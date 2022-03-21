#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

#include <string_view>
#include <unordered_map>
#include <vector>

namespace nped {

class CmdlineOptionParser {
public:
    CmdlineOptionParser(int argc, char *argv[]);
    std::vector<std::string_view> get_opt(std::string_view flag);
private:
    uint8_t arg_prefix_len(char *arg);

    std::unordered_map<std::string_view, std::vector<std::string_view>> args_;
};

}

#endif // OPTION_PARSER_H
