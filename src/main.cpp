#include <iostream>
#include <QLabel>
#include <QApplication>
#include "edgedetector.hpp"
#include "accumulator.hpp"
#include "argparser.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    bugDepth::EdgeDetector detector;
    Accumulator accumulator;

    auto filenames = bugDepth::ArgParser::prepareImageFileNames("res/bug/");

    for (auto& filename: filenames)
    {
        QImage testImage(filename.c_str());
        QImage edges = detector.sobel(testImage);
        accumulator.accumulate(testImage, edges);
    }

    QImage bgImage = QImage(filenames[0].c_str());
    accumulator.setBg(bgImage);

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(accumulator.getAcumulated()));
    myLabel.show();

    return app.exec();
}
