#include <stdio.h>

#include "capture.h"

#define EXIT_FAIL -1

bool args_ok(int argc);

int main(int argc, char *argv[]) {
//    if (!args_ok(argc)) { 
//        return -1;
//    }

    nped::PacketSniffer ps(nped::SnifferType::FileSniffer,
                           "enp0s25",
                           "");
    ps.run_sniffer();
}

bool args_ok(int argc) {
    if (argc < 2) {
        printf("Usage: # ./nped [options]\n"
               "  options:\n"
               "example: # \n"
               "description: Edits captured network packet fields"
               "note: Needs to be run as root.\n");
        return false;
    }
    return true;
}
