#include <iostream>
#include <QLabel>
#include <QApplication>
#include "edgedetector.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QImage testImage("/home/asalle/me/projects/BugDepth/res/bug/b_bigbug0000_croppped.png");

    EdgeDetector detector;
    QImage grayscale = testImage.convertToFormat(QImage::Format_Grayscale8);
    QImage edges = detector.sobel(grayscale);

    QLabel myLabel;
    myLabel.setPixmap(QPixmap::fromImage(edges));

    myLabel.show();

    return app.exec();
}
