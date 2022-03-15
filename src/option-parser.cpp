#include "option-parser.h"

#include <stdexcept>

namespace nped {

CmdlineOptionParser::CmdlineOptionParser(int argc, char *argv[]) {
    if (argc < 3 || argc > 5) {
        throw std::runtime_error("Usage: ./nped -i INTERFACE -f FILTER");
    }
    args_.reserve(argc - 1);
    for (uint8_t i = 1; i < argc; ++i) {
        args_.emplace_back(argv[i]);
    }
}

std::string_view CmdlineOptionParser::get_opt(std::string_view flag) {
    for (auto it = args_.begin(); it < args_.end(); ++it) {
        if (*it == flag) {
            return it + 1 == args_.end() ? "" : *(it + 1);
        }
    }
    return "";
}
}
