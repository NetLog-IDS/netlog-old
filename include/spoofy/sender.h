#ifndef _SENDER_H_
#define _SENDER_H_
#include "isender.h"

// Follows the list of delays incrementally, starting from the smallest delay first
class KafkaSender : public ISender {
    virtual void send() const;
};

// Follows the list of delays decrementally, starting from the highest delay first
class NetworkSender : public ISender {
    virtual void send() const;
};
#endif // _SENDER_H_
