/* Header */
#include <catch2/catch_test_macros.hpp>

#include <tins/tins.h>
#include <vector>
// what do we need to do?
// edit a network packet, so first we need a real packet
#include "spoofy/sniffer.h" 
#include "spoofy/utils/queue.h"

struct PacketStorer {
    std::vector<Tins::Packet> orig;
    std::vector<Tins::Packet> modified;
};

struct TestContext {
    TestContext(const char *file_path, const char *filter) : 
        sniffer_({ spoofy::SnifferType::FileSniffer, file_path, filter}) {}

    spoofy::PacketSniffer sniffer_;
    ThreadSafeQueue<Tins::Packet> queue_;
    PacketStorer store_;
};

TestContext* init_ctx() {
    static TestContext c("/home/adrian/dis/captures/1st.pcap", "");

    bool running = true;
    c.sniffer_.run(c.queue_, running);
    
    return &c;
}

void spoof_ip_ecn(Tins::Packet& p) {
    Tins::PDU *pdu = p.pdu();

    // get IP layer
    Tins::IP *ipv4 = pdu->find_pdu<Tins::IP>();
    Tins::IPv6 *ipv6 = pdu->find_pdu<Tins::IPv6>();

    if (ipv4 != NULL) {
        // look for tos - ecn
    }

    if (ipv6 != NULL) {
        //look for traffic class - ecn
    }
}

int do_stuff() {
    TestContext *tc = init_ctx();

    while (!tc->queue_.empty()) {
        Tins::Packet p = tc->queue_.pop();
        tc->store_.orig.push_back(p);

//        do modifications on the packet
        //        search and replace the ECN field in TOS/diffserv/trafic classipv6
    }
    
    return 0;
}

/* Impl */
TEST_CASE("Default", "[def]") {
    REQUIRE(do_stuff() == 0);
}
