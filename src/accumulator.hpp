#pragma once

#include <QImage>

class Accumulator
{
public:
    Accumulator(unsigned int width, unsigned int height);
    void accumulate(QImage& original, QImage& grayScale);
    void setBg(QImage& bg);
    QImage getAcumulated() const;

private:
    QImage accumulated;
};
