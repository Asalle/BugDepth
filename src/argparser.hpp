#pragma once

#include <string>
#include <vector>

namespace bugDepth {

class ArgParser
{
public:
    // vector will be moved thanks to copy ellision
    static std::vector<std::string> prepareImageFileNames(std::string&& path);
    ArgParser() = delete;
    ArgParser(ArgParser&) = delete;
    ArgParser(const ArgParser&) = delete;
    ArgParser(ArgParser&&) = delete;
};

}
