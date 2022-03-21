#include "option-parser.h"

#include <stdexcept>

namespace nped {

CmdlineOptionParser::CmdlineOptionParser(int argc, char *argv[]) {
    args_.reserve(argc - 1);
    std::vector<std::string_view> basic_args; 

    uint8_t i = 0;
    while (i < argc) {
        uint8_t trim = arg_prefix_len(argv[i]);

        std::string_view sv { argv[i] };
        sv.remove_prefix(trim);

        if (trim) {
            ++i;
            std::vector<std::string_view> flag_args;
            while (i < argc && arg_prefix_len(argv[i]) == 0) {
                flag_args.emplace_back(argv[i]);
                ++i;
            }
            std::pair<std::string_view,
                    std::vector<std::string_view>> arg_pair(sv, flag_args);
            args_.insert(arg_pair);
        } else {
            basic_args.push_back(sv);
            ++i;
        }
    }
    std::pair<std::string_view,
                std::vector<std::string_view>> arg_pair("args", basic_args);
    args_.insert(arg_pair);
}

std::vector<std::string_view>
CmdlineOptionParser::get_opt(std::string_view flag) {
    try {
        return args_.at(flag);
    } catch (std::out_of_range& e) {
        throw std::invalid_argument("Invalid input arguments.");
    }
}

uint8_t CmdlineOptionParser::arg_prefix_len(char *argv) {
    if (argv[0] == '-' && argv[1] == '-') {
        return 2;
    } else if (argv[0] == '-') {
        return 1;
    } else {
        return 0;
    }
}
}
