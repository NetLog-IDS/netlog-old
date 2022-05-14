#ifndef _SENDER_H_
#define _SENDER_H_

class ISender {
public:
    virtual ~ISender() {}
    virtual void send() = 0;
};

class SendingContext {
public:
    SendingContext(ISender *sender);
    ~SendingContext();

    void send_packet();

    void set_sender(ISender *sender);
private:
    ISender *sender_;
};

#endif // _SENDER_H_
