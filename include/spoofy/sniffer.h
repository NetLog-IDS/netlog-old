#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include<memory>

#include <tins/tins.h>

#include "spoofy/utils/queue.h"

namespace spoofy {

enum class SnifferType { Sniffer, FileSniffer };

/**
 * @class PacketSniffer
 *
 * @brief Responsible for setting up and running the packet capture process via
 * the libtins library.
 * */
class PacketSniffer {
public:
    PacketSniffer(SnifferType st, const char *iface, const char *capture_filter);
    PacketSniffer() = delete;

    void run(ThreadSafeQueue<Tins::Packet>& packetq, bool &running);
private:
    void setup(SnifferType st, const char *iface, const char *capture_filter);
    bool callback(Tins::Packet& packet,
                  ThreadSafeQueue<Tins::Packet>& packetq,
                  bool &running);

    std::unique_ptr<Tins::BaseSniffer> sniffer_;
};
}
#endif // _CAPTURE_H_
