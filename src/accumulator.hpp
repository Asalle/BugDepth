#pragma once

#include "img.hpp"

namespace bugDepth {

class Accumulator
{
public:
    Accumulator(uint width, uint height);
    void accumulate(RgbImg &original, GrayImg &grayScale, int depth);
    void setBg(RgbImg &backGround);
    RgbImg& getSharpImage();
    GrayImg& getDepthMap();

private:
    template<typename T>
    void copy3InRow(T *dest, const T *src, int x)
    {
        dest[x] = src[x];
        dest[x-1] = src[x-1];
        dest[x+1] = src[x+1];
    }

    template<typename T>
    void set3inRow(T *dest, uint value, int x)
    {
        dest[x] = value;
        dest[x-1] = value;
        dest[x+1] = value;
    }

    RgbImg sharpImage;
    GrayImg depthMap;
    uint treshold = 0x55;
    uint depthMapThreshold = 0x40;
};

}
