#include <stdexcept>
#include <iostream>

#include "capture.h"
#include "utils/option-parser.h"


int main(int argc, char *argv[]) {
//    try {
        nped::CmdlineOptionParser opt_parser(argc, argv);

        auto args = opt_parser.args();
        auto flags = opt_parser.flags();
        auto switches = opt_parser.switches();

//        if (iface.size() != 1 || filter.empty()) {
//            throw std::invalid_argument("Invalid input arguments");
//        }
//
//        std::string pcap_filter = "";
//        for (auto s: filter) {
//            pcap_filter.append(s);
//            pcap_filter.append(" ");
//        }
//
//        nped::PacketSniffer ps(nped::SnifferType::FileSniffer,
//                               iface[0].data(),
//                               pcap_filter.data());
//
//        ps.run_sniffer();
//    } catch (std::invalid_argument& e) {
//        std::cerr << e.what() << std::endl;
//        std::cerr << "Usage: ./nped -i INTERFACE -f filter" << std::endl;
//        return -1;
//    } catch (std::exception& e) {
//        std::cerr << e.what() << std::endl;
//        return -1;
//    }
    return 0;
}
