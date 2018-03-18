#pragma once

#include <QImage>

#include "img.hpp"

namespace bugDepth {

using GrayImg = Img<Format::GRAYSCALE8>;

class EdgeDetector
{
public:
    GrayImg sobel(Img<Format::RGBA32> input);
private:
    void magnitude(QImage& input, const QImage& gx, const QImage& gy);
    QImage convolution(const auto& kernel, const QImage& image);
    GrayImg convertToGrayScale(Img<Format::RGBA32> original);
};

}
