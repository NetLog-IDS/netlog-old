#include "option-parser.h"

#include <stdexcept>


namespace nped {

CmdlineOptionParser::CmdlineOptionParser(int argc, char *argv[]) {
    int i = 0;
    while (i < argc) {
        uint8_t prefix = arg_prefix_len(argv[i]);
        std::string_view arg { argv[i] };
        arg.remove_prefix(prefix);
        if (!prefix) {
            // Store regular argument
            arguments_.push_back(arg);
            ++i;
            continue;
        }

        int j = i; // keep a copy, in case switches are not found
        // Store the switch 
        if (is_switch(argv, argc, i++)) {
            if (prefix == 1) {
                SwitchPair sp(SwitchType::MULTI, arg);
                switches_.push_back(sp);
                continue;
            }
            SwitchPair sp(SwitchType::SINGLE, arg);
            switches_.push_back(sp);
            continue;
        }

        // Store a pair consisting of the flag name and flag arguments
        ArgVector flag_args = get_flag_args(argv, argc, j);
        NamedPair flag_pair(arg, flag_args); 
        flags_.push_back(flag_pair);

        i = j; // restore initial value
    }
}

// Returns the argument prefix length
// Used to determine if string is flag (single/double-dash) or argument
uint8_t CmdlineOptionParser::arg_prefix_len(char *argv) {
    if (argv[0] == '-' && argv[1] == '-') {
        return 2;
    } else if (argv[0] == '-') {
        return 1;
    } else {
        return 0;
    }
}

bool CmdlineOptionParser::is_switch(char *argv[], int argc, int pos) {
    if (pos + 1 == argc) {
        return true;
    } 
    if (arg_prefix_len(argv[pos]) != 0 && arg_prefix_len(argv[pos + 1]) != 0) {
        return true;
    }
    return false;
}

CmdlineOptionParser::ArgVector 
CmdlineOptionParser::get_flag_args(char *argv[], int argc, int& pos) {
    ++pos;
    CmdlineOptionParser::ArgVector flag_args;
    while (pos < argc && arg_prefix_len(argv[pos]) == 0) {
        flag_args.emplace_back(argv[pos]);
        ++pos;
    }
    return flag_args;
}

const CmdlineOptionParser::NamedPairVector& 
CmdlineOptionParser::flags() const { return flags_; }

const CmdlineOptionParser::SwitchPairVector& 
CmdlineOptionParser::switches() const { return switches_; }

const CmdlineOptionParser::ArgVector& 
CmdlineOptionParser::args() const { return arguments_; }

}
