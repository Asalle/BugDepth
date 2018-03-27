#pragma once

//#include <QImage>
#include "img.hpp"

namespace bugDepth {

class Accumulator
{
public:
    Accumulator(unsigned int width, unsigned int height);
    void accumulate(RgbImg& original, GrayImg& grayScale, int depth);
    void setBg(RgbImg& bg);
    RgbImg getSharpImage() const;
    GrayImg getDepthMap() const;

private:
    RgbImg sharpImage;
    GrayImg depthMap;
    unsigned int treshold = 0x55;
    unsigned int depthMapThreshold = 0x40;
};

}
