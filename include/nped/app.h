#ifndef _APP_H_
#define _APP_H_

#include <tins/tins.h>
#include <cclap/cclap.h>

#include "nped/utils/queue.h"

namespace nped {

class Application {
public:
    Application(int argc, char *argv[]);

    Application() = delete;
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    void operator=(const Application&) = delete;
    void operator=(Application&&) = delete;

    void start();
private:
    cclap::ArgParser arg_parser_;
//    PacketEditor editor_;

    ThreadSafeQueue<Tins::Packet> packetq_;
    std::vector<Tins::Packet> edited_packets_;
};

}

#endif // _APP_H_
