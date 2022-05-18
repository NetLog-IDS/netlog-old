#ifndef _SPOOFER_H_
#define _SPOOFER_H_

#include "ispoofer.h"

// Follows the list of delays incrementally, starting from the smallest delay first
class IncrementalDelaySpoofer : public ISpoofer {
    virtual void spoof() const;
};

// Follows the list of delays decrementally, starting from the highest delay first
class DecrementalDelaySpoofer : public ISpoofer {
    virtual void spoof() const;
};

// Randomly picks from the list of delays
class RandomDelaySpoofer : public ISpoofer {
    virtual void spoof() const;
};

#endif // _SPOOFER_H_
