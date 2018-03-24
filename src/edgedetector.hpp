#pragma once

#include <QImage>

#include "img.hpp"

namespace bugDepth {

using GrayImg = Img<Format::GRAYSCALE8>;
using RgbImg = Img<Format::RGBA32>;

class EdgeDetector
{
public:
    GrayImg sobel(Img<Format::RGBA32>& input);
private:
    void magnitude(GrayImg& input, GrayImg gx, const GrayImg& gy);
    GrayImg convolution(const auto& kernel, const GrayImg& image);
    GrayImg convertToGrayScale(Img<Format::RGBA32> original);
};

}
