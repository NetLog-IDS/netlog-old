#ifndef CAPJSON_CAPTURE_H
#define CAPJSON_CAPTURE_H

#include<memory>

#include <tins/tins.h>

namespace nped {

enum class SnifferType { Sniffer, FileSniffer };

class PacketSniffer {
public:
    PacketSniffer(SnifferType st, const char *iface, const char *ptype);

    PacketSniffer() = delete;

    void run();
private:
    void setup(SnifferType st, const char *iface, const char *ptype);
    bool callback(Tins::PDU& pdu);

    std::unique_ptr<Tins::BaseSniffer> sniffer_;
};
}
#endif //CAPJSON_CAPTURE_H
