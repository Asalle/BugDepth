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

    QImage sampleImage(filenames.front().c_str());
    const uint width = sampleImageMat.width();
    const uint height = sampleImageMat.height();

    bugDepth::EdgeDetector detector;
    bugDepth::Accumulator accumulator(width, height);
    int depth = 0x10;
    for (auto& filename: filenames)
    {
        QImage readImg(filename.c_str());
        bugDepth::RgbImg testImage(width, height, readImg.bits());
        bugDepth::GrayImg edges = detector.sobel(testImage);
        accumulator.accumulate(testImage, edges, depth);
        depth += 0x10;
    }

    bugDepth::RgbImg sampleImage(width, height, sampleImageMat.bits());
    accumulator.setBg(sampleImage);
    auto resultdir = prepareResultDir();

    auto res = accumulator.getSharpImage();
    QImage result(res.getData(), res.getWidth(), res.getHeight(), QImage::Format_RGB32);
    result.save(resultdir.filePath("result.png"));

    auto resDepthMap = accumulator.getDepthMap();
    QImage resultDepth(resDepthMap.getData(), resDepthMap.getWidth(), resDepthMap.getHeight(), QImage::Format_Grayscale8);
    resultDepth.save(resultdir.filePath("depthMap.png"));
    return 0;
}
