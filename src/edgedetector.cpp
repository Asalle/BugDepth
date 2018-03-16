#include <cmath>
#include <ctgmath>

#include "edgedetector.hpp"

namespace bugDepth {

template<class T, size_t Rows, size_t Cols> using matrix = std::array<std::array<T, Cols>, Rows>;
const matrix<int, 3, 3> sobelx {{ {{-1, 0, 1}}, {{-2, 0, 2}}, {{-1, 0, 1}} }};
const matrix<int, 3, 3> sobely {{ {{1, 2, 1}}, {{0, 0, 0}}, {{-1, -2, -1}} }};

QImage EdgeDetector::sobel(QImage& original) {
    QImage input = convertToGrayScale(original);
    QImage res(input.size(), input.format());
    magnitude(res, convolution(sobelx, input), convolution(sobely, input));
    return res;
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

QImage EdgeDetector::convertToGrayScale(QImage &original)
{
    return original.convertToFormat(QImage::Format_Grayscale8);
}

}
