#ifndef _SNIFFER_H_
#define _SNIFFER_H_

#include <memory>
#include <atomic>

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

    void run(ThreadSafeQueue<Tins::Packet>& packetq, std::atomic_bool &running);
private:
//    bool callback(const Tins::Packet &packet, ThreadSafeQueue<Tins::Packet> &packetq, bool &running);
    void setup(SnifferType st, const char *iface, const char *capture_filter);

    SnifferType sniffer_type_;
    std::unique_ptr<Tins::BaseSniffer> sniffer_;
};
}
#endif // _SNIFFER_H_
