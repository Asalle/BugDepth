#pragma once

namespace bugDepth {

struct Img
{
    Img(unsigned int width, unsigned int height, unsigned char *data);
    unsigned int width;
    unsigned int height;
    unsigned char *data;
};

}
