#include "spoofy/app.h"

#include <memory>
#include <atomic>
#include <stdexcept>
#include <string>
#include <thread>
#include <iostream>
#include <optional>

#include "spoofy/sniffer.h"
#include "spoofy/sender.h"

namespace spoofy {

struct ApplicationContext {
    ApplicationContext(int argc, char *argv[]) : arg_parser_(argc, argv) {}

    struct CliArgs {
        std::string interface_name;
        SnifferType sniffer_type;
        std::string capture_filter;
        std::optional<std::string> sending_interface;
        std::optional<std::string> broker, topic;
    } args_;


    cclap::ArgParser arg_parser_;
    ThreadSafeQueue<Tins::Packet> packetq_;
    std::vector<Tins::Packet> edited_packets_;
};

/**
 * @brief Class constructor.
 * @param[in] argc Number of application input arguments
 * @param[in] argv List of command line arguments
 * @return Application object
 * */
Application::Application(int argc, char *argv[]) : ctx_(std::make_unique<ApplicationContext>(argc, argv)) {
    setup();
}

Application::~Application() = default;

/**
 * @brief Contains the high-level application logic.
 * */
void Application::start() { 
    std::atomic_bool running(true);

    try {
        // Start capturing packets and store them in a queue
        std::thread sniffer([&pq = ctx_->packetq_, &st = ctx_->args_.sniffer_type, &running,
                             &iface = ctx_->args_.interface_name, &filter = ctx_->args_.capture_filter]() { 
                                 PacketSniffer ps(st, iface.data(), filter.data());
                                 ps.run(pq, running);
                                 running.store(false); // stop running after sniffing all packets
                             });

        // Consume the packets stored in the queue and send them to Apache Kafka
        std::thread kafka_producer([&pq = ctx_->packetq_, &edp = ctx_->edited_packets_, &running]() {
                                 Sender s(std::make_unique<KafkaSender>("broker_name", "topic_name"));
                                 while (running || !pq.empty()) {
                                     if (!pq.empty()) {
                                         Tins::Packet pkt(pq.pop()); 
                                         edp.push_back(pkt); //push them into a container just in case

                                         s.send_packet(pkt);
                                     }
                                 } 
                             });

        if (ctx_->args_.sniffer_type == SnifferType::Sniffer) {
            // Listen for user input to stop live capture
            std::cout << "[INFO] Live capture started on interface: " << ctx_->args_.interface_name << std::endl;
            std::thread wait_for_key([&running]() {
                                         std::cout << "Press key to stop capture";
                                         std::cin.get();

                                         running.store(false);
                                     });
            wait_for_key.join();
        } 
        sniffer.join();
        kafka_producer.join();
    } catch (const std::exception &e) {
        throw std::runtime_error(e.what());
        return;
    }

    if (ctx_->args_.sniffer_type == SnifferType::FileSniffer) {
        std::cout << "[INFO] Read packets from capture file: " << ctx_->args_.interface_name << std::endl; 
    }

    std::cout << "[INFO] Work is done! Processed "<< ctx_->edited_packets_.size() << " packets.\n" << "Press any key to exit...\n";
    std::cin.get();
}

void Application::setup() {
    // get sniffer type (read from file or live capture)
    ctx_->args_.sniffer_type = ctx_->arg_parser_.find_switch("l") ||
        ctx_->arg_parser_.find_switch("live") ? SnifferType::Sniffer : SnifferType::FileSniffer;

    // get specified interface name, or default network interface
    const auto &interface_found= ctx_->arg_parser_.find_flag("i");
    ctx_->args_.interface_name = [&interface_found] {
        if (!interface_found) {
            Tins::NetworkInterface ni = Tins::NetworkInterface::default_interface();
            const std::string interface_name(ni.name());
            std::cout << "[INFO] Network interface not specified, using default.\n";
            return interface_name;
        }
        return std::string(interface_found.value()[0].data());
    }();

    // get capture flags or empty string if not specified
    const auto &filter_found = ctx_->arg_parser_.find_flag("f");
    ctx_->args_.capture_filter = [&filter_found] {
        std::string res = "";
        if (!filter_found) {
            return res;
        }

        for (auto &s: filter_found.value()) {
            res.append(s);
            res.append(" ");
        }
        res.pop_back();
        return res;
    }();

    const auto &sender_found = ctx_->arg_parser_.find_flag("sender");
    if (!sender_found) {
        throw std::runtime_error("[ERROR - CLI args] Sender not specified.");
    }

    ctx_->args_.sending_interface = std::invoke([this, &sender_found]() -> std::optional<std::string> {
        if (!(sender_found.value()[0] == "network")) { 
            return std::nullopt;
        }

        const auto &sinterface_found = ctx_->arg_parser_.find_flag("network-sending-interface");
        if(!sinterface_found) {
            return std::nullopt; // don't throw, if no interface is provided we will use the one from the capture
        }
        return std::make_optional<std::string>(sinterface_found.value()[0]);
    });

    ctx_->args_.broker = std::invoke([this, &sender_found]() -> std::optional<std::string> {
        if (!(sender_found.value()[0] == "kafka")) { 
            return std::nullopt;
        }

        const auto &broker_found = ctx_->arg_parser_.find_flag("broker");
        if(!broker_found) {
            throw std::runtime_error("[ERROR - CLI args] Kafka broker not specified");
        }
        return std::make_optional<std::string>(broker_found.value()[0]);
        /* if(!sender_found) {
            return std::nullopt;
        }
        return std::make_optional<std::string>(sender_found.value()[0]); */
    });

    ctx_->args_.topic = std::invoke([this]() -> std::optional<std::string> {
        if (!ctx_->args_.broker) {
            return std::nullopt;
        }
        
        const auto &topic_found = ctx_->arg_parser_.find_flag("topic");
        if (!topic_found) {
            throw std::runtime_error("[ERROR - CLI args] Kafka topic not specified");
        }
        return std::make_optional<std::string>(topic_found.value()[0]);
    });
}

}

