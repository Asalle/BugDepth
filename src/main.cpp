#include <iostream>
#include <QLabel>
#include <QApplication>
#include <QDirIterator>
#include <vector>
#include "edgedetector.hpp"
#include "accumulator.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    EdgeDetector detector;
    Accumulator accumulator;

    std::vector<std::string> filenames;
    QDirIterator it("res/bug/");
    while (it.hasNext())
    {
        QString filePath = it.next();
        QString fileName = it.fileInfo().fileName();
        if (fileName == ".." or fileName == "." or fileName == "result.png")
        {
            continue;
        }
        filenames.emplace_back(filePath.toStdString());
    }

    std::sort(filenames.begin(), filenames.end());
    std::reverse(filenames.begin(), filenames.end());

    for (auto& filename: filenames)
    {
        QImage testImage(filename.c_str());

        QImage grayscale = testImage.convertToFormat(QImage::Format_Grayscale8);
        QImage edges = detector.sobel(grayscale);

        accumulator.accumulate(testImage, edges);
    }

    QImage bgImage = QImage(filenames[0].c_str());
    accumulator.setBg(bgImage);

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(accumulator.getAcumulated()));
    myLabel.show();

    return app.exec();
}
