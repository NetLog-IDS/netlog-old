#include <stdexcept>
#include <iostream>

#include <cclap/cclap.h>
#include "capture.h"

int main(int argc, char *argv[]) {
    try {
        cclap::ArgParser ap(argc, argv);

        // Get args
        auto args = ap.args();
        auto flags = ap.flags();
        auto switches = ap.switches();

        // Search for interface and filters
        auto iface = ap.find_flag("i");
        auto filter = ap.find_flag("f");

        // Interface is mandatory for now, TODO capture from default interface if none is specified
        if (!iface) {
            throw std::invalid_argument("Invalid input arguments");
        }

        // Populate filters if present
        std::string pcap_filter = "";
        if (filter) {
            for (auto s: filter.value()) {
                pcap_filter.append(s);
                pcap_filter.append(" ");
            }
            pcap_filter.pop_back();
        }

        nped::PacketSniffer ps(nped::SnifferType::FileSniffer,
                               iface.value()[0].data(),
                               pcap_filter.data());

        ps.run_sniffer();
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./nped -i INTERFACE -f filter" << std::endl;
        return -1;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
