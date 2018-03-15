#include "img.hpp"

namespace bugDepth {

Img::Img(unsigned int w, unsigned int h, unsigned char *d)
    : width(w)
    , height(h)
    , data(d)
{
}

}
