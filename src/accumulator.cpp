#include "accumulator.hpp"
#include <iostream>
#include <QPixmap>
#include <QLabel>

Accumulator::Accumulator()
    : accumulated(QPixmap(1344, 1021).toImage())
{
}

void Accumulator::accumulate(QImage& original, QImage& grayScale)
{
//    QLabel myLabel;
//    myLabel.setPixmap(QPixmap::fromImage(original));
//    myLabel.show();

    std::cout << original.height() << " " << original.width() << std::endl;

    for (int y = 0; y < original.height(); y++) {
//        uchar* grayline = grayScale.scanLine(y);
        uchar* origLine = original.scanLine(y);
        uchar* acumLine = accumulated.scanLine(y);
        memcpy(acumLine, origLine, original.width());

//        for (int x = 0; x < original.height(); x++) {
////            QColor color = QColor::fromRgb(grayline[x]);
////            int c, m, y, k, al;
////            color.getCmyk(&c, &m, &y, &k, &al);
////            if (c == 0 && m == 0 && y == 0 && k == 0)
////            {
//                int val = origLine[x];
//                std::cout << origLine[x] << " ";
////                if (acumLine[x] == 0x00)
////                    acumLine[x] = 0x51;
//                    acumLine[x] = qBound(0x00, val, 0xFF);
////            }
//        }
    }
}

QImage Accumulator::getAcumulated() const
{
    return accumulated;
}
