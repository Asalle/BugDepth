#pragma once

#include <QImage>

namespace bugDepth {

class EdgeDetector
{
public:
    QImage sobel(QImage& input);
private:
    void magnitude(QImage& input, const QImage& gx, const QImage& gy);
    QImage convolution(const auto& kernel, const QImage& image);
    QImage convertToGrayScale(QImage& original);
};

}
