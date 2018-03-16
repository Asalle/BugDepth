#include <cmath>
#include <ctgmath>

#include "edgedetector.hpp"

#include <iostream>
#include <opencv2/opencv.hpp>

namespace bugDepth {

template<class T, size_t Rows, size_t Cols> using matrix = std::array<std::array<T, Cols>, Rows>;
const matrix<int, 3, 3> sobelx {{ {{-1, 0, 1}}, {{-2, 0, 2}}, {{-1, 0, 1}} }};
const matrix<int, 3, 3> sobely {{ {{1, 2, 1}}, {{0, 0, 0}}, {{-1, -2, -1}} }};

Img EdgeDetector::sobel(Img original) {
    Img input = convertToGrayScale(original);
//    QImage res(input.size(), input.format());
//    magnitude(res, convolution(sobelx, input), convolution(sobely, input));
    return input;
}

void EdgeDetector::magnitude(QImage& input, const QImage& gx, const QImage& gy) {
    quint8 *line = nullptr;
    const quint8 *gx_line = nullptr, *gy_line = nullptr;

    for (int y = 0; y < input.height(); y++) {
        line = input.scanLine(y);
        gx_line = gx.constScanLine(y);
        gy_line = gy.constScanLine(y);

        for (int x = 0; x < input.width(); x++)
            line[x] = qBound(0x00, static_cast<int>(hypot(gx_line[x], gy_line[x])), 0xFF);
    }
}

QImage EdgeDetector::convolution(const auto& kernel, const QImage& image) {
    int kw = kernel[0].size(), kh = kernel.size(),
        offsetx = kw / 2, offsety = kw / 2;
    QImage out(image.size(), image.format());
    float sum = 0;

    quint8 *line = nullptr;
    const quint8 *lookup_line = nullptr;

    for (int y = 0; y < image.height(); y++) {
        line = out.scanLine(y);
        for (int x = 0; x < image.width(); x++) {
            sum = 0;

            for (int j = 0; j < kh; j++) {
                if (y + j < offsety || y + j >= image.height())
                    continue;
                lookup_line = image.constScanLine(y + j - offsety);
                for (int i = 0; i < kw; i++) {
                    if (x + i < offsetx || x + i >= image.width())
                        continue;
                    sum += kernel[j][i] * lookup_line[x + i - offsetx];
                }
            }

            line[x] = qBound(0x00, static_cast<int>(sum), 0xFF);
        }
    }

    return out;
}

Img EdgeDetector::convertToGrayScale(Img original)
{
    int height = original.height;
    int width = original.width;

    uchar *grayScale = new uchar[height*width];
    for (int y = 0; y < height; ++y)
    {
        uchar* origLine = original.data + (y*width*4);
        uchar* grayLine = grayScale  + (y*width);
        int grayX = 0;
        for (int x = 0; x < width; x+=4)
        {
            uchar r = origLine[x];
            uchar g = origLine[x+1];
            uchar b = origLine[x+2];
            uchar a = origLine[x+3];
            grayLine[grayX] = (r + g + b + a)/4;
            grayX++;
        }

    }

    return Img(width, height, grayScale);
//    return original.convertToFormat(QImage::Format_Grayscale8);
}

}
