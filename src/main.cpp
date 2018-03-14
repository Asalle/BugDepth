#include <iostream>
#include <QLabel>
#include <QApplication>
#include <QDirIterator>
#include "edgedetector.hpp"
#include "accumulator.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    EdgeDetector detector;
//    Accumulator accumulator;

    QDirIterator it("res/bug/");
//    while (it.hasNext())
//    {
        QImage testImage(it.next());

        QString fileName = it.fileInfo().fileName();
        if (fileName == ".." or fileName == "." or fileName == "result.png");
//            continue;

        QImage grayscale = testImage.convertToFormat(QImage::Format_Grayscale8);
        QImage edges = detector.sobel(grayscale);

//        accumulator.accumulate(testImage, edges);
//    }

    QImage result = QPixmap(grayscale.width(), grayscale.height()).toImage();
    for (int y = 0; y < testImage.height(); y++) {
//        uchar* grayline = grayScale.scanLine(y);
        uchar* origLine = testImage.scanLine(y);
        uchar* acumLine = result.scanLine(y);
//        memcpy(acumLine, origLine, original.width());

        for (int x = 0; x < testImage.width(); x++) {
////            QColor color = QColor::fromRgb(grayline[x]);
////            int c, m, y, k, al;
////            color.getCmyk(&c, &m, &y, &k, &al);
////            if (c == 0 && m == 0 && y == 0 && k == 0)
////            {
                int val = origLine[x];
//                std::cout << origLine[x] << " ";
////                if (acumLine[x] == 0x00)
////                    acumLine[x] = 0x51;
                    acumLine[x] = qBound(0x00, val, 0xFF);
////            }
        }
    }

    QLabel myLabel;
//    myLabel.setPixmap(QPixmap::fromImage(accumulator.getAcumulated()));
    myLabel.setPixmap(QPixmap::fromImage(result));
    myLabel.show();

    return app.exec();
}
