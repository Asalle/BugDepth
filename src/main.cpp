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
    auto filenames = bugDepth::ArgParser::prepareImageFileNames("res/bug/");

    QImage sampleQImage(filenames.front().c_str());
    const uint width = sampleQImage.width();
    const uint height = sampleQImage.height();

    bugDepth::EdgeDetector detector;
    bugDepth::Accumulator accumulator(width, height);

    int depth = 0x10;
    for (auto& filename: filenames)
    {
        QImage inImage(filename.c_str());
        bugDepth::RgbImg testImage(width, height, inImage.bits());
        bugDepth::GrayImg edges = detector.sobel(testImage);
        accumulator.accumulate(testImage, edges, depth);
        depth += 0x20;
    }

    bugDepth::RgbImg sampleImage(width, height, sampleQImage.bits());
    accumulator.setBg(sampleImage);

    auto resultdir = prepareResultDir();

    auto sharpImage = accumulator.getSharpImage();
    QImage sharpQImage(sharpImage.getData(), width, height, QImage::Format_RGB32);
    sharpQImage.save(resultdir.filePath("result.png"));

    auto depthMap = accumulator.getDepthMap();
    QImage depthMapQImage(depthMap.getData(), width, height, QImage::Format_Grayscale8);
    depthMapQImage.save(resultdir.filePath("depthMap.png"));
    return 0;
}
