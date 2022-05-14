#ifndef _SENDER_H_
#define _SENDER_H_

class ISender {
public:
    virtual ~ISender() {}
    virtual void send() = 0;
};

#endif // _SENDER_H_
