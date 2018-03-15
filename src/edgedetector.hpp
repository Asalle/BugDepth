#pragma once

#include <QImage>

#include "img.hpp"

namespace bugDepth {

class EdgeDetector
{
public:
    Img sobel(Img input);
private:
    void magnitude(QImage& input, const QImage& gx, const QImage& gy);
    QImage convolution(const auto& kernel, const QImage& image);
    Img convertToGrayScale(Img original);
};

}
