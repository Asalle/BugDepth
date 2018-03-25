#pragma once

#include <vector>

namespace bugDepth {

using uchar = unsigned char;
using uint = unsigned int;
constexpr uint RGBBPP = 3;

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
    const uchar* getData() const { return data.data(); }
    uchar* scanLine(int y);
    const uchar* constScanLine(int y) const;

private:
    uint width;
    uint height;
    std::vector<uchar> data;
};

}
