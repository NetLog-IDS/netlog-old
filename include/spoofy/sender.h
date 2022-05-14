#include "isender.h"

class SendingContext {
public:
    SendingContext(ISender *sender);
    ~SendingContext();

    void send_packet();

    void set_sender(ISender *sender);
private:
    ISender *sender_;
};

// Follows the list of delays incrementally, starting from the smallest delay first
class KafkaSender : public ISender {
    virtual void send() const;
};

// Follows the list of delays decrementally, starting from the highest delay first
class NetworkSender : public ISender {
    virtual void send() const;
};
