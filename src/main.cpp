#include <stdio.h>

#include "capture.h"
#include "option-parser.h"


int main(int argc, char *argv[]) {
    nped::CmdlineOptionParser opt_parser(argc, argv);

    nped::PacketSniffer ps(nped::SnifferType::FileSniffer,
                           opt_parser.get_opt("-i").data(),
                           opt_parser.get_opt("-f").data());

    ps.run_sniffer();
}
