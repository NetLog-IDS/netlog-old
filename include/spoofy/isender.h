#ifndef _ISENDER_H_
#define _ISENDER_H_

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

#endif // _ISENDER_H_
