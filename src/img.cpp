#include "img.hpp"

#include <opencv2/opencv.hpp>

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
    , data(w*h*bpp[f], 0)
{
    unsigned int imageBpp = bpp[f];
    for (int y = 0; y < height; ++y)
    {
       auto *origLine = f == Format::GRAYSCALE8 ? (d + y*width) : (reinterpret_cast<unsigned int*>(d + y*width));
       for (int x = 0; x < width*imageBpp; ++x)
       {
           data[y*width*imageBpp+x] = origLine[x];
       }
    }

    cv::Mat mat(height, width, CV_8UC4);
    mat.data = reinterpret_cast<unsigned char*>(data.data());

    cv::imshow("constrIm", mat);
    cv::waitKey(0);

}

}
