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
    , data(w*h*sizeof(uint))
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
    , data(w*h*sizeof(uint), 0)
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

}
