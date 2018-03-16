#include <algorithm>
#include <experimental/filesystem>

#include "argparser.hpp"

namespace bugDepth {

using std::experimental::filesystem::directory_iterator;

std::vector<std::string> ArgParser::prepareImageFileNames(std::string &&path)
{
    std::vector<std::string> filenames;
    for (auto& file: directory_iterator(path))
    {
        if (file.path() == "res/bug/result.png")
            continue;

        filenames.emplace_back(file.path());
    }

    std::sort(filenames.begin(), filenames.end());
    std::reverse(filenames.begin(), filenames.end());

    return filenames;
}

}
