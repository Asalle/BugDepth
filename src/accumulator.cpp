#include "accumulator.hpp"
#include <algorithm>

namespace bugDepth {

Accumulator::Accumulator(unsigned int width, unsigned int height)
    : sharpImage(width, height)
    , depthMap(width, height)
{
}

void Accumulator::accumulate(RgbImg &image, GrayImg &grayScale, int depth)
{
    uint *pastLineOrig = nullptr;
    uint *pastLineRes = nullptr;

    for (int y = 0; y < image.getHeight(); y++) {
        uint *resultLine = reinterpret_cast<uint*>(sharpImage.scanLine(y));
        uint *origLine = reinterpret_cast<uint*>(image.scanLine(y));
        uchar *grayLine = grayScale.scanLine(y);
        uchar *depthMapLine = depthMap.scanLine(y);
        for (int x = 1; x < image.getWidth()-1; x++) {
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

                uint *nextOrigLine = reinterpret_cast<uint*>(image.scanLine(y+1));
                uint *nextResLine = reinterpret_cast<uint*>(sharpImage.scanLine(y+1));
                nextResLine[x] = nextOrigLine[x];
                nextResLine[x-1] = nextOrigLine[x-1];
                nextResLine[x+1] = nextOrigLine[x+1];
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

void Accumulator::setBg(RgbImg &bg)
{
    for (int y = 0; y < bg.getHeight(); y++) {
        uint *acline = reinterpret_cast<uint*>(sharpImage.scanLine(y));
        uint *bgline = reinterpret_cast<uint*>(bg.scanLine(y));

        for (int x = 0; x < bg.getWidth(); x++) {
            if (acline[x] < 0x10)
                acline[x] = bgline[x];
        }
    }
}

RgbImg Accumulator::getSharpImage() const
{
    return sharpImage;
}

GrayImg Accumulator::getDepthMap() const
{
    return depthMap;
}

}
