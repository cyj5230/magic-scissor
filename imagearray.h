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
    int getRed(int vecIndex){return vecRed[vecIndex];}
    int getGreen(int vecIndex){return vecGreen[vecIndex];}
    int getBlue(int vecIndex){return vecBlue[vecIndex];}
    void setRed(int vecIndex, int r){vecRed[vecIndex] = r;}
    void setGreen(int vecIndex, int g){vecGreen[vecIndex] = g;}
    void setBlue(int vecIndex, int b){vecBlue[vecIndex] = b;}
    ~imArray();

private:
    int width, height;
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

imArray::~imArray()
{

}

#endif // IMAGEARRAY_H
