#ifndef _SPOOFER_H_
#define _SPOOFER_H_

class ISpoofer {
public:
    virtual ~ISpoofer() {}
    virtual void spoof() = 0;
};

#endif // _SPOOFER_H_
