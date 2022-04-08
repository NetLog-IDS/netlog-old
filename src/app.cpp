#include "nped/app.h"

#include <stdexcept>
#include <string>
#include <thread>

#include "nped/sniffer.h"

namespace nped {

Application::Application(int argc, char *argv[]) : arg_parser_{argc, argv} { }

void Application::start() { 
    try {
        // Search for interface and filters
        auto sniff_path = arg_parser_.find_flag("i");
        auto filter = arg_parser_.find_flag("f");

        if (!sniff_path) {
            throw std::invalid_argument("Invalid input arguments");
        }

        const SnifferType st = 
            arg_parser_.find_switch("l") || arg_parser_.find_switch("live") ? 
            SnifferType::Sniffer : SnifferType::FileSniffer;

        // Populate filters 
        std::string pcap_filter = "";
        if (filter) {
            for (auto s: filter.value()) {
                pcap_filter.append(s);
                pcap_filter.append(" ");
            }
            pcap_filter.pop_back();
        }


        // TODO start thread for keypress detection to stop capture -- nested lambda?
        //
        // TODO start a second thread for live capture

        PacketSniffer ps(st, sniff_path.value()[0].data(), pcap_filter.data());

        // TODO thread 1 - capture packets -- accesses packet pool
        ps.run();

        // TODO thread 2 - edit packets -- accesses packet pool
        //        PacketEditor pe;
        //        pe.edit_next_packet(PacketPool& p);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

}
