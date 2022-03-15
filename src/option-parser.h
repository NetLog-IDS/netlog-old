#ifndef OPTION_PARSER_H
#define OPTION_PARSER_H

#include <string_view>
#include <vector>

namespace nped {
class CmdlineOptionParser {
public:
    CmdlineOptionParser(int argc, char *argv[]);
    std::string_view get_opt(std::string_view flag);
private:
    std::vector<std::string_view> args_;
};
}

#endif // OPTION_PARSER_H
