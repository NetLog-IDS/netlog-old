#ifndef _APP_H_
#define _APP_H_
#include <memory>

#include <tins/tins.h>
#include <cclap/cclap.h>

#include "spoofy/utils/queue.h"

namespace spoofy {

struct ApplicationContext;

/**
 * @class Application
 * @brief Manages application data and initiates program execution.
 * */
class Application {
public:
    Application(int argc, char *argv[]);
    ~Application();

    Application() = delete;
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    void operator=(const Application&) = delete;
    void operator=(Application&&) = delete;

    void setup();
    void start();
private:
    std::unique_ptr<ApplicationContext> ctx_;
};

}

#endif // _APP_H_
