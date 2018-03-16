#include <iostream>
#include <QLabel>
#include <QApplication>
#include "edgedetector.hpp"
#include "accumulator.hpp"
#include "argparser.hpp"
#include "img.hpp"

#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    bugDepth::EdgeDetector detector;
    Accumulator accumulator;

    auto filenames = bugDepth::ArgParser::prepareImageFileNames("res/bug/");

    QImage im(filenames[0].c_str());
    bugDepth::Img rawIm(im.width(), im.height(), bugDepth::Format::RGBA32);
//    bugDepth::Img edges = detector.sobel(rawIm);
//    cv::Mat mat(im.height(), im.width(), CV_8UC1);
//    mat.data = edges.data;

//    cv::imshow("mainImg", mat);
//    cv::waitKey(0);

//    delete edges.data;

//    for (auto& filename: filenames)
//    {
//        QImage testImage(filename.c_str());
//        bugDepth::Img rawImage(testImage.width(), testImage.height(), testImage.bits());
//        bugDepth::Img edges = detector.sobel(rawImage);
////        accumulator.accumulate(testImage, edges);
//    }

//    QImage bgImage = QImage(filenames[0].c_str());
//    accumulator.setBg(bgImage);

//    QLabel myLabel;
//    myLabel.setPixmap(QPixmap::fromImage(accumulator.getAcumulated()));
//    myLabel.show();

//    return app.exec();
    return 0;
}
