#include "img.hpp"

namespace bugDepth {

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

}
