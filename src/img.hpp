#pragma once

#include <vector>

namespace bugDepth {

using uchar = unsigned char;
using uint = unsigned int;

enum class Format : uchar
{
    GRAYSCALE8,
    RGBA32
};

template<Format format>
class Img
{
public:
    Img(uint width, uint height);
    Img(uint width, uint height, uchar* data);
    uint getWidth() const { return width; }
    uint getHeight() const { return height; }
    uchar* getData() { return data.data(); }

private:
    uint width;
    uint height;
    std::vector<uchar> data;
};

}
