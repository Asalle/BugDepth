#pragma once

#include <QImage>

class Accumulator
{
public:
    Accumulator(unsigned int width, unsigned int height);
    void accumulate(QImage& original, QImage& grayScale, int depth);
    void setBg(QImage& bg);
    QImage getSharpImage() const;
    QImage getDepthMap() const;

private:
    QImage sharpImage;
    QImage depthMap;
    unsigned int treshold = 0x55;
    unsigned int depthMapThreshold = 0x40;
};
