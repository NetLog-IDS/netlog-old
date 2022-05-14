#include "spoofy/sniffer.h"

#include <iostream>
#include <exception>
#include <functional>

namespace spoofy {

/**
 * @brief Class constructor.
 * @param[in] st Type of Sniffer used in the packet capture process.
 * @param[in] iface Name of interface on which to run the capture. Can be a
 * file path, if using the file sniffer.
 * @param[in] capture_filter Type of packet to capture, contains PCAP filter
 * @returns PacketSniffer object
 * */
PacketSniffer::PacketSniffer(SnifferType st,
                             const char *iface,
                             const char *capture_filter) { 
    setup(st, iface, capture_filter);
}

/**
 * @brief Setup function. Used to initialize all the sniffer parameters.
 * @param[in] st Type of Sniffer used in the packet capture process.
 * @param[in] iface Name of interface on which to run the capture. Can be a
 * file path, if using the file sniffer.
 * @param[in] capture_filter Type of packet to capture, contains PCAP filter
 * */
void PacketSniffer::setup(SnifferType st, const char *iface, const char *capture_filter) {
    Tins::SnifferConfiguration config;
    config.set_promisc_mode(true);
    config.set_filter(capture_filter);

    try {
        if (st == SnifferType::FileSniffer) {
            sniffer_ = std::make_unique<Tins::FileSniffer>(iface, config);
        } else {
            sniffer_ = std::make_unique<Tins::Sniffer>(iface, config);
        }
    } catch (Tins::pcap_error &e) {
        throw std::runtime_error(e.what());
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief Callback function. This gets called each time a packet is captured.
 * @param[in] packet Captured packet.
 * @param[in] packetq Queue used to store the captured packets.
 * @param[in] running Boolean used to manage running state, and end the capture
 * when needed.
 * */
bool
PacketSniffer::callback(Tins::Packet &packet,
                        ThreadSafeQueue<Tins::Packet> &packetq,
                        bool &running) { 
    packetq.push(packet);
    return running;
}

/**
 * @brief Run function. Used to bind values provided via the API to the callback
 * function.
 * @param[in] packetq Queue used to store the captured packets.
 * @param[in] running Boolean used to manage running state, and end the capture
 * when needed.
 * */
void PacketSniffer::run(ThreadSafeQueue<Tins::Packet> &packetq, bool &running) {
    try {
        sniffer_->sniff_loop(std::bind(&PacketSniffer::callback, this,
                                       std::placeholders::_1, std::ref(packetq),
                                       std::ref(running)));
    } catch (std::exception &ex) {
        throw std::runtime_error(ex.what());
    }
}

}
