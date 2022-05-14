#include "ispoofer.h"

#include <vector>

class SpoofingContext {
public:
    SpoofingContext(ISpoofer *spoofer);
    ~SpoofingContext();

    void do_spoofing();

    void set_spoofer(ISpoofer *spoofer);
    void set_delays(const std::vector<int> &d);
private:
    ISpoofer *spoofer_;
    const std::vector<int> &delays;
};

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
