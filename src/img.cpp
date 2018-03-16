#include "img.hpp"

namespace bugDepth {

using uchar = unsigned char;

Img::Img(unsigned int w, unsigned int h, Format f)
    : bpp{
            {Format::GRAYSCALE8, 1},
            {Format::RGBA32, 4}
         }
    , width(w)
    , height(h)
    , format(f)
    , data(w*h*bpp[f])
{
}

std::vector<unsigned char>& Img::getData()
{
    return data;
}

bugDepth::Img::Img(unsigned int w, unsigned int h, bugDepth::Format f, unsigned char *d)
    : bpp{
            {Format::GRAYSCALE8, 1},
            {Format::RGBA32, 4}
         }
    , width(w)
    , height(h)
    , format(f)
    , data(w*h*bpp[f])
{
    unsigned int imageBpp = bpp[f];
   for (int y = 0; y < height; ++y)
   {
       uchar *origLine = d + y*width*imageBpp;
       for (int x = 0; x < width*imageBpp; ++x)
       {
//           data[y*width*imageBpp+x] = (d + y*width*imageBpp+x)[0];
           data[y*width*imageBpp+x] = origLine[x];
       }
   }
}

}
