#ifndef IMAGEARRAY_H
#define IMAGEARRAY_H

#include <QPixmap>
#include <QVector>
#include <QRgb>

// currently only deal with rgb images

class imArray
{
public:

    explicit imArray(QImage *image);
    ~imArray();

private:
    double width, height;
    QVector<int> vecRed;
    QVector<int> vecGreen;
    QVector<int> vecBlue;
};



imArray::imArray(QImage *image)
{
    this->width = image->width();
    this->height = image->height();
    for(int haxis = 0; haxis < this->height; haxis++){
        QRgb* line = (QRgb*)image->scanLine(haxis);
        for(int waxis = 0; waxis < this->width; waxis++){
            QRgb pixelInfo = line[waxis];
            this->vecBlue.append(qBlue(pixelInfo));
            this->vecGreen.append(qGreen(pixelInfo));
            this->vecRed.append(qRed(pixelInfo));
        }
    }
}

#endif // IMAGEARRAY_H