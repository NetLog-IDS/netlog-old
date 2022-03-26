#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

#include <string_view>
#include <vector>
#include <utility>

namespace nped {

class CmdlineOptionParser {
public:
    typedef std::string_view ArgName;
    typedef std::vector<ArgName> ArgVector;
    typedef std::pair<ArgName, ArgVector> NamedPair;
    typedef std::vector<NamedPair> NamedPairVector;

    // Single Switch - Singular switch (e.g: -i -o -a --sort)
    // Multi Switch - Multiple options (e.g.: -ioa)
    enum class SwitchType { SINGLE, MULTI };
    typedef std::pair<SwitchType, ArgName> SwitchPair;
    typedef std::vector<SwitchPair> SwitchPairVector;

public:
    CmdlineOptionParser(int argc, char *argv[]);
    const NamedPairVector& flags() const;
    const SwitchPairVector& switches() const;
    const ArgVector& args() const;

private:
    ArgVector get_flag_args(char *argv[], int argc, int& pos);
    uint8_t arg_prefix_len(char *arg);
    bool is_switch(char *arg_v[], int argc, int pos);

    NamedPairVector flags_;
    SwitchPairVector switches_;
    ArgVector arguments_;
};

}

#endif // OPTION_PARSER_H
