#include <algorithm>
#include <array>
#include <cmath>
#include <ctgmath>

#include "edgedetector.hpp"

// most of this file is from github.com/vaultah/edge-detection/, modified

namespace bugDepth {

template<class T, size_t Rows, size_t Cols> using matrix = std::array<std::array<T, Cols>, Rows>;
const matrix<int, 3, 3> sobelx {{ {{-1, 0, 1}}, {{-2, 0, 2}}, {{-1, 0, 1}} }};
const matrix<int, 3, 3> sobely {{ {{1, 2, 1}}, {{0, 0, 0}}, {{-1, -2, -1}} }};

GrayImg EdgeDetector::sobel(Img<Format::RGBA32>& original) {
    uint width = original.getWidth();
    uint height = original.getHeight();
    GrayImg input(width, height);
    convertToGrayScale(original, input);
    GrayImg res(width, height);
    GrayImg convolutionX(width, height);
    GrayImg convolutionY(width, height);
    convolution(sobelx, input, convolutionX);
    convolution(sobely, input, convolutionY);

    magnitude(res, convolutionX, convolutionY);
    return res;
}

void EdgeDetector::magnitude(GrayImg& input, const GrayImg& gx, const GrayImg& gy) {
    for (int y = 0; y < input.getHeight(); ++y) {
        uchar *line = input.scanLine(y);
        const uchar *gx_line = gx.constScanLine(y);
        const uchar *gy_line = gy.constScanLine(y);
        for (int x = 0; x < input.getWidth(); ++x)
        {
            line[x] = std::min(std::max(0x00, static_cast<int>(hypot(gx_line[x], gy_line[x]))), 0xFF);
        }
    }
}

void EdgeDetector::convolution(const auto& kernel, const GrayImg& image, GrayImg& out) {
    int kw = kernel[0].size(), kh = kernel.size(),
        offsetx = kw / 2, offsety = kw / 2;

    float sum = 0;

    uchar *line = nullptr;
    const uchar *lookup_line = nullptr;

    for (int y = 0; y < image.getHeight(); y++) {
        line = out.scanLine(y);
        for (int x = 0; x < image.getWidth(); x++) {
            sum = 0;

            for (int j = 0; j < kh; j++) {
                if (y + j < offsety || y + j >= image.getHeight())
                    continue;
                lookup_line = image.constScanLine(y + j - offsety);
                for (int i = 0; i < kw; i++) {
                    if (x + i < offsetx || x + i >= image.getWidth())
                        continue;
                    sum += kernel[j][i] * lookup_line[x + i - offsetx];
                }
            }

            line[x] = std::min(std::max(0x00, static_cast<int>(sum)), 0xFF);
        }
    }
}

void EdgeDetector::convertToGrayScale(const RgbImg &original, GrayImg& grayScaleImg)
{
    int height = original.getHeight();
    int width = original.getWidth();
    auto bpp = bugDepth::RGBBPP;

    for (int y = 0; y < height; ++y)
    {
        const uchar *sourceLine = original.constScanLine(y);
        uchar *grayLine = grayScaleImg.scanLine(y);
        int grayX = 0;
        for (int x = 0; x < width*bpp; x+=bpp)
        {
            uchar b = sourceLine[x];
            uchar g = sourceLine[x+1];
            uchar r = sourceLine[x+2];
            grayLine[grayX] = (r + g + b)/3;
            grayX++;
        }
    }
}

}
