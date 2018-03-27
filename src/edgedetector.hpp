#pragma once

//#include <QImage>

#include "img.hpp"

namespace bugDepth {

class EdgeDetector
{
public:
    GrayImg sobel(Img<Format::RGBA32>& input);
private:
    void magnitude(GrayImg& input, const GrayImg& gx, const GrayImg& gy);
    GrayImg convolution(const auto& kernel, const GrayImg& image, GrayImg& out);
    void convertToGrayScale(const Img<Format::RGBA32>& original, GrayImg& grayScaleImg);
};

}
