#include "spoofy/app.h"

#include <memory>
#include <atomic>
#include <stdexcept>
#include <string>
#include <thread>
#include <iostream>

#include "spoofy/sniffer.h"
#include "spoofy/sender.h"

namespace spoofy {

struct ApplicationContext {
    ApplicationContext(int argc, char *argv[]) : arg_parser_(argc, argv) {}

    struct CliArgs {
        std::string interface_name;
        SnifferType sniffer_type;
        std::string capture_filter;
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
        // Start capturing packets
        std::thread producer([&pq = ctx_->packetq_, &st = ctx_->args_.sniffer_type, &running,
                             &iface = ctx_->args_.interface_name, &filter = ctx_->args_.capture_filter]() { 
                                 PacketSniffer ps(st, iface.data(), filter.data());
                                 ps.run(pq, running);
                                 running.store(false); // stop running after sniffing all packets
                             });

        // Start processing packets
        std::thread consumer([&pq = ctx_->packetq_, &edp = ctx_->edited_packets_, &running]() {
                                 while (running) {
                                     if (!pq.empty()) {
                                         // processing on the packets here
                                         Tins::Packet pkt(pq.pop()); // avoid copy
                                         edp.push_back(pkt); // just to make sure the previous code works 
                                         // do some packet processing/spoofing here 
                                         // SPOOF
                                         // convert to JSON or some format
                                         // JSONIFY
                                         // produce the message to kafka here
                                         // this should be all that needs to be done, the implementation should be hidden away
                                         Sender s(std::make_unique<KafkaSender>());
                                         s.send_packet(pkt);
                                     }
                                 } 
                             });

       if (ctx_->args_.sniffer_type == SnifferType::Sniffer) {
            // Listen for user input to stop capture
            std::cout << "[INFO] Live capture started on interface: " << ctx_->args_.interface_name << std::endl;
            std::thread wait_for_key([&running, &producer, &consumer]() {
                                         std::cout << "Press key to stop capture";
                                         std::cin.get();

                                         running.store(false);
                                     });
            wait_for_key.join();
       } 
        producer.join();
        consumer.join();
    } catch (const std::exception &e) {
        throw std::runtime_error(e.what());
        return;
    }
    std::cout << "[INFO] Reading packets from capture file: " << ctx_->args_.interface_name << std::endl; 

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
    const auto& filter_found = ctx_->arg_parser_.find_flag("f");
    ctx_->args_.capture_filter = [&filter_found] {
        std::string res = "";
        if (!filter_found) {
            return res;
        }

        for (auto& s: filter_found.value()) {
            res.append(s);
            res.append(" ");
        }
        res.pop_back();
        return res;
    }();
}

}

