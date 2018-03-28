#include "img.hpp"

namespace bugDepth {

template<>
Img<Format::GRAYSCALE8>::Img(uint w, uint h)
    : width(w)
    , height(h)
    , data(w*h*sizeof(uchar))
{
}

template<>
Img<Format::RGBA32>::Img(uint w, uint h)
    : width(w)
    , height(h)
    , data(w*h*RGBBPP)
{
}

template<>
Img<Format::GRAYSCALE8>::Img(uint w, uint h, uchar *dataToCopy)
    : width(w)
    , height(h)
    , data(w*h*sizeof(uchar), 0)
{
    for (int y = 0; y < height; ++y)
    {
       auto *sourceLine = dataToCopy + y*width;
       for (int x = 0; x < width; ++x)
       {
           data[y*width+x] = sourceLine[x];
       }
    }
}

template<>
Img<Format::RGBA32>::Img(uint w, uint h, uchar *dataToCopy)
    : width(w)
    , height(h)
    , data(w*h*RGBBPP, 0)
{
    for (int y = 0; y < height; ++y)
    {
       auto *origLine = reinterpret_cast<uint*>(dataToCopy) + y*width;
       auto *selfLine = reinterpret_cast<uint*>(data.data()) + y*width;
       for (int x = 0; x < width; ++x)
       {
           selfLine[x] = origLine[x];
       }
    }
}

template<>
uchar* Img<Format::RGBA32>::scanLine(int y)
{
    return reinterpret_cast<uchar*>(data.data() + y*width*RGBBPP);
}

template<>
uchar* Img<Format::GRAYSCALE8>::scanLine(int y)
{
    return data.data() + y*width*sizeof(uchar);
}

template<>
const uchar* Img<Format::RGBA32>::constScanLine(int y) const
{
    return reinterpret_cast<const uchar*>(data.data() + y*width*RGBBPP);
}

template<>
const uchar* Img<Format::GRAYSCALE8>::constScanLine(int y) const
{
    return data.data() + y*width*sizeof(uchar);
}

}
