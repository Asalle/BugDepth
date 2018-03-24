#include <opencv2/opencv.hpp>
//#include <QDir>
#include "accumulator.hpp"
#include "argparser.hpp"
#include "edgedetector.hpp"

//QDir prepareResultDir()
//{
//    QDir resultdir("res/result");
//    if (resultdir.exists())
//        resultdir.removeRecursively();
//    resultdir.mkpath(".");

//    return resultdir;
//}

auto main() -> int
{
    bugDepth::EdgeDetector detector;
    auto filenames = bugDepth::ArgParser::prepareImageFileNames("res/bug/");

    cv::Mat sampleImage = cv::imread(filenames[0].c_str(), CV_LOAD_IMAGE_COLOR);
    const uint width = sampleImage.size().width;
    const uint height = sampleImage.size().height;
    Accumulator accumulator(width, height);

    int depth = 0x10;
    for (auto& filename: filenames)
    {
        cv::Mat testImageMat = cv::imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);
        bugDepth::RgbImg testImage(width, height, testImageMat.data);
        bugDepth::GrayImg edges = detector.sobel(testImage);
        cv::Mat temp(edges.getHeight(), edges.getWidth(), CV_8UC1, edges.getData());
        cv::imwrite("res/result.png", temp);
//        accumulator.accumulate(testImage, edges, depth);
        depth += 0x10;
    }

//    accumulator.setBg(sampleImage);

//    auto resultdir = prepareResultDir();

//    QImage&& result = accumulator.getSharpImage();
//    result.save(resultdir.filePath("result.png"));

//    QImage&& depthMap = accumulator.getDepthMap();
//    depthMap.save(resultdir.filePath("depthMap.png"));

    return 0;
}
