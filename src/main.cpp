#include <iostream>
#include <stdexcept>

#include "nped/app.h"

int main(int argc, char *argv[]) {
    try {
        nped::Application app(argc, argv);
        app.start();
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ./nped -i <iface | file> [-f filter] [-l | --live]\n";
        return -1;
    }
}
