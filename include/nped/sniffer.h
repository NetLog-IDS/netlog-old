#ifndef CAPJSON_CAPTURE_H
#define CAPJSON_CAPTURE_H

#include<memory>

#include <tins/tins.h>

#include "nped/utils/queue.h"

namespace nped {

enum class SnifferType { Sniffer, FileSniffer };

/**
 * @class PacketSniffer
 *
 * @brief Responsible for setting up and running the packet capture process via
 * the libtins library.
 * */
class PacketSniffer {
public:
    PacketSniffer(SnifferType st, const char *iface, const char *ptype);
    PacketSniffer() = delete;

    void run(ThreadSafeQueue<Tins::Packet>& packetq, bool &running);
private:
    void setup(SnifferType st, const char *iface, const char *ptype);
    bool callback(Tins::Packet& packet,
                  ThreadSafeQueue<Tins::Packet>& packetq,
                  bool &running);

    std::unique_ptr<Tins::BaseSniffer> sniffer_;
};
}
#endif //CAPJSON_CAPTURE_H
