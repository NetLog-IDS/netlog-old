#include "nped/sniffer.h"

#include <iostream>
#include <exception>
#include <functional>

namespace nped {

PacketSniffer::PacketSniffer(SnifferType st,
                             const char *iface,
                             const char *ptype) { 
    setup(st, iface, ptype);
}

void PacketSniffer::setup(SnifferType st, const char *iface, const char *ptype) {
    Tins::SnifferConfiguration config;
    config.set_promisc_mode(true);
    config.set_filter(ptype);

    try {
        if (st == SnifferType::FileSniffer) {
            sniffer_ = std::make_unique<Tins::FileSniffer>(iface, config);
        } else {
            sniffer_ = std::make_unique<Tins::Sniffer>(iface, config);
        }
    } catch (Tins::pcap_error &e) {
        throw std::runtime_error("Invalid path to '.pcap' file.");
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

bool PacketSniffer::callback(Tins::PDU& pdu) { 
    return true;
}

void PacketSniffer::run() {
    try {
        sniffer_->sniff_loop(std::bind(
                               &PacketSniffer::callback,
                               this,
                               std::placeholders::_1));
    } catch (std::exception &ex) {
        throw std::runtime_error(ex.what());
    }
}

}
