#include <string>

#include "argparser.hpp"
#include "gtest/gtest.h"

TEST (testArgParser, shouldReturnFilesInReverseLexicographicalOrder) {
    auto pathToDirWithImages = "res/bug/";
    std::vector<std::string> expected{
        "res/bug/b_bigbug0012_croppped.png",
        "res/bug/b_bigbug0011_croppped.png",
        "res/bug/b_bigbug0010_croppped.png",
        "res/bug/b_bigbug0009_croppped.png",
        "res/bug/b_bigbug0008_croppped.png",
        "res/bug/b_bigbug0007_croppped.png",
        "res/bug/b_bigbug0006_croppped.png",
        "res/bug/b_bigbug0005_croppped.png",
        "res/bug/b_bigbug0004_croppped.png",
        "res/bug/b_bigbug0003_croppped.png",
        "res/bug/b_bigbug0002_croppped.png",
        "res/bug/b_bigbug0001_croppped.png",
        "res/bug/b_bigbug0000_croppped.png",
    };
    auto imageNames = bugDepth::ArgParser::prepareImageFileNames(pathToDirWithImages);

    EXPECT_EQ(imageNames.size(), expected.size());
    for (uint i = 0; i < imageNames.size(); ++i)
    {
        EXPECT_EQ(imageNames[i], expected[i]);
    }
}
