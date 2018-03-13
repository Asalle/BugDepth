#pragma once

#include <QImage>

class EdgeDetector
{
public:
    QImage sobel(const QImage& input);
private:
    void magnitude(QImage& input, const QImage& gx, const QImage& gy);
    QImage convolution(const auto& kernel, const QImage& image);
};
