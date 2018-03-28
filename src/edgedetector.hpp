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
    void convolution(const auto& kernel, const GrayImg& image, GrayImg& out);
    void convertToGrayScale(const RgbImg& original, GrayImg& grayScaleImg);
};

}
