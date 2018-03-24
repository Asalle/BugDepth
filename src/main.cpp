#include <opencv2/opencv.hpp>
#include <QDir>
#include <QImage>
#include "accumulator.hpp"
#include "argparser.hpp"
#include "edgedetector.hpp"

QDir prepareResultDir()
{
    QDir resultdir("res/result");
    if (resultdir.exists())
        resultdir.removeRecursively();
    resultdir.mkpath(".");

    return resultdir;
}

auto main() -> int
{
    bugDepth::EdgeDetector detector;
    auto filenames = bugDepth::ArgParser::prepareImageFileNames("res/bug/");

    QImage sampleImage(filenames[0].c_str());
    Accumulator accumulator(sampleImage.width(), sampleImage.height());

    int depth = 0x10;
    for (auto& filename: filenames)
    {
        QImage testImage(filename.c_str());
        QImage edges = detector.sobel(testImage);
        accumulator.accumulate(testImage, edges, depth);
        depth += 0x10;
    }
    accumulator.setBg(sampleImage);

    auto resultdir = prepareResultDir();

    QImage&& result = accumulator.getSharpImage();
    result.save(resultdir.filePath("result.png"));

    QImage&& depthMap = accumulator.getDepthMap();
    depthMap.save(resultdir.filePath("depthMap.png"));

    return 0;
}
