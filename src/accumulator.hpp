#pragma once

#include <QImage>

class Accumulator
{
public:
    Accumulator();
    void accumulate(QImage& original, QImage& grayScale);
    void setBg(QImage& bg);
    QImage getAcumulated() const;

private:
    QImage accumulated;
};
