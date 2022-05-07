/* Header */
#include <catch2/catch_test_macros.hpp>

// what do we need to do?
// edit a network packet, so first we need a real packet
#include "nped/sniffer.h" 

nped::PacketSniffer create_packet_sniffer() {
    return nped::PacketSniffer(nped::SnifferType::FileSniffer, "/home/adrian/dis/captures/1st.pcap", ""); 
}

int empty_test() {
    nped::PacketSniffer ps = create_packet_sniffer();
    return 0;
}

/* Impl */
TEST_CASE("Default", "[def]") {
    REQUIRE(empty_test() == 0);
}
