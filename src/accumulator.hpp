#pragma once

#include <QImage>

class Accumulator
{
public:
    Accumulator();
    void accumulate(QImage& original, QImage& grayScale);
    QImage getAcumulated() const;

private:
    QImage accumulated;
};
