#include <QApplication>
#include <QImage>
#include <QDir>
#include "edgedetector.hpp"
#include "accumulator.hpp"
#include "argparser.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    bugDepth::EdgeDetector detector;

    auto filenames = bugDepth::ArgParser::prepareImageFileNames("res/bug/");
    QImage sampleImage(filenames[0].c_str());
    Accumulator accumulator(sampleImage.width(), sampleImage.height());

    for (auto& filename: filenames)
    {
        QImage testImage(filename.c_str());
        QImage edges = detector.sobel(testImage);
        accumulator.accumulate(testImage, edges);
    }

    accumulator.setBg(sampleImage);

    QDir resultdir("res/result");
    if (resultdir.exists())
        resultdir.removeRecursively();
    resultdir.mkpath(".");

    QImage&& result = accumulator.getAcumulated();
    result.save(resultdir.filePath("result.png"));

    QImage&& depthMap = detector.sobel(result);
    depthMap.save(resultdir.filePath("depthMap.png"));

    return 0;
}
