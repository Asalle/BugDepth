#include "accumulator.hpp"
#include <algorithm>

Accumulator::Accumulator(unsigned int width, unsigned int height)
    : sharpImage(width, height, QImage::Format::Format_ARGB32)
    , depthMap(width, height, QImage::Format::Format_Grayscale8)
{
}

void Accumulator::accumulate(QImage &image, QImage &grayScale, int depth)
{
    QRgb *pastLineOrig = nullptr;
    QRgb *pastLineRes = nullptr;

    for (int y = 0; y < image.height(); y++) {
        QRgb *resultLine = reinterpret_cast<QRgb*>(sharpImage.scanLine(y));
        QRgb *origLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        quint8 *grayLine = grayScale.scanLine(y);
        quint8 *depthMapLine = depthMap.scanLine(y);
        for (int x = 1; x < image.width()-1; x++) {
            if (resultLine[x] == 0x00 && grayLine[x] > treshold) {
                resultLine[x] = origLine[x];
                resultLine[x-1] = origLine[x-1];
                resultLine[x+1] = origLine[x+1];

                if (pastLineOrig and pastLineRes)
                {
                    pastLineRes[x] = pastLineOrig[x];
                    pastLineRes[x-1] = pastLineOrig[x-1];
                    pastLineRes[x+1] = pastLineOrig[x+1];
                }
            }

            if (grayLine[x] > depthMapThreshold)
            {
                auto actualDepth = std::min(depth, 0xff);
                depthMapLine[x] = actualDepth;
                depthMapLine[x-1] = actualDepth;
                depthMapLine[x+1] = actualDepth;
            }
        }
        pastLineRes = resultLine;
        pastLineOrig = origLine;
    }
}

void Accumulator::setBg(QImage &bg)
{
    QRgb *acline;
    QRgb *bgline;

    for (int y = 0; y < bg.height(); y++) {
        acline = reinterpret_cast<QRgb*>(sharpImage.scanLine(y));
        bgline = reinterpret_cast<QRgb*>(bg.scanLine(y));

        for (int x = 0; x < bg.width(); x++) {
            if (acline[x] < 0x10)
                acline[x] = bgline[x];
        }
    }
}

QImage Accumulator::getSharpImage() const
{
    return sharpImage;
}

QImage Accumulator::getDepthMap() const
{
    return depthMap;
}
