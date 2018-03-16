#pragma once

#include <map>
#include <vector>

namespace bugDepth {

enum class Format : unsigned char
{
    GRAYSCALE8,
    RGBA32
};

class Img
{
public:
    Img(unsigned int width, unsigned int height, Format format);
    Img(unsigned int width, unsigned int height, Format format, unsigned char* data);
    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }
    std::vector<unsigned char>& getData();

private:
    std::map<Format, unsigned int> bpp;
    unsigned int width;
    unsigned int height;
    std::vector<unsigned char> data;
    Format format;
};

}
