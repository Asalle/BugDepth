#include "accumulator.hpp"
#include <algorithm>

namespace bugDepth {

Accumulator::Accumulator(uint width, uint height)
    : sharpImage(width, height)
    , depthMap(width, height)
{
}

void Accumulator::accumulate(RgbImg &original, GrayImg &grayScale, int depth)
{
    uint width = original.getWidth();
    uint height = original.getHeight();

    for (int y = 1; y < height-1; y++)
    {
        uint *midDestLine = reinterpret_cast<uint*>(sharpImage.scanLine(y));
        uint *midSrcLine = reinterpret_cast<uint*>(original.scanLine(y));

        uchar *grayLine = grayScale.scanLine(y);
        uchar *depthMapLine = depthMap.scanLine(y);

        uint *pastLineRes = reinterpret_cast<uint*>(sharpImage.scanLine(y-1));
        uint *pastLineOrig = reinterpret_cast<uint*>(original.scanLine(y-1));

        uint *nextOrigLine = reinterpret_cast<uint*>(original.scanLine(y+1));
        uint *nextResLine = reinterpret_cast<uint*>(sharpImage.scanLine(y+1));
        for (int x = 1; x < width-1; x++)
        {
            if (midDestLine[x] == 0x00 && grayLine[x] > treshold)
            {
                copy3InRow(midDestLine, midSrcLine, x);
                copy3InRow(pastLineRes, pastLineOrig, x);
                copy3InRow(nextResLine, nextOrigLine, x);
            }

            if (grayLine[x] > depthMapThreshold)
            {
                auto actualDepth = std::min(depth, 0xff);
                set3inRow(depthMapLine, actualDepth, x);
            }
        }
    }
}

void Accumulator::setBg(RgbImg &bg)
{
    for (int y = 0; y < bg.getHeight(); y++)
    {
        uint *destline = reinterpret_cast<uint*>(sharpImage.scanLine(y));
        uint *bgline = reinterpret_cast<uint*>(bg.scanLine(y));

        for (int x = 0; x < bg.getWidth(); x++)
        {
            if (destline[x] < 0x10)
                destline[x] = bgline[x];
        }
    }
}

RgbImg& Accumulator::getSharpImage()
{
    return sharpImage;
}

GrayImg& Accumulator::getDepthMap()
{
    return depthMap;
}

}
