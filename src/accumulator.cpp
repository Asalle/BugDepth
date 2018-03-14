#include "accumulator.hpp"
#include <iostream>
#include <QPixmap>
#include <QLabel>

Accumulator::Accumulator()
    : accumulated(QPixmap(1344, 1021).toImage())
{
}

void Accumulator::accumulate(QImage &image, QImage &grayScale)
{
    QImage& out = accumulated;
    QRgb *line;
    QRgb *imLine;
    quint8 *grayLine;
    for (int y = 0; y < image.height(); y++) {
        line = reinterpret_cast<QRgb*>(out.scanLine(y));
        imLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        grayLine = grayScale.scanLine(y);
        for (int x = 0; x < image.width(); x++) {
            if (line[x] == 0x00 && grayLine[x] > 0x55)
                line[x] = imLine[x];
        }
    }
}

void Accumulator::setBg(QImage &bg)
{
    QRgb *acline;
    QRgb *bgline;

    for (int y = 0; y < bg.height(); y++) {
        acline = reinterpret_cast<QRgb*>(accumulated.scanLine(y));
        bgline = reinterpret_cast<QRgb*>(bg.scanLine(y));

        for (int x = 0; x < bg.width(); x++) {
            if (acline[x] < 0x10)
                acline[x] = bgline[x];
        }
    }
}

QImage Accumulator::getAcumulated() const
{
    return accumulated;
}
