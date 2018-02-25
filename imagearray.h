#ifndef IMAGEARRAY_H
#define IMAGEARRAY_H

#include <QPixmap>
#include <QImage>
#include <QVector>
#include <QRgb>
#include <QDebug>
#include <QVarLengthArray>

// currently only deal with rgb images

class imArray
{
public:
    QVarLengthArray<bool> vecEdge, vecBorder, vecTempEdge, vecTempBorder;

    // input functions
    void setImage(QImage *image){
        this->width = (int)image->width();
        this->height = (int)image->height();
        for(int haxis = 0; haxis < this->height; haxis++){
            QRgb* line = (QRgb*)image->scanLine(haxis);
            for(int waxis = 0; waxis < this->width; waxis++){
                // construct color array
                QRgb pixelInfo = line[waxis];
                this->vecBlue.append(qBlue(pixelInfo));
                this->vecGreen.append(qGreen(pixelInfo));
                this->vecRed.append(qRed(pixelInfo));

                // construct edge & border array
                this->vecEdge.append(false);
                this->vecBorder.append(false);
                this->vecTempEdge.append(false);
                this->vecTempBorder.append(false);
            }
        }
        qDebug() << "Image Size: " << this->width << "x" << this->height;
        qDebug() << "has alpha channel:" <<image->hasAlphaChannel() << "image format:" << image->format();
        qDebug() << "pixel number:" << vecEdge.count() << vecBorder.count();
    }

    // output functions
    int getHeight(){return(this->height);}
    int getWidth(){return(this->width);}
    int getRed(int loc){return vecRed.at(loc);}
    int getGreen(int loc){return vecGreen.at(loc);}
    int getBlue(int loc){return vecBlue.at(loc);}

    // change cordinator to index
    int vecloc(int w, int h){return h * this->width + w;}

private:
    int width, height;
    QVarLengthArray<int> vecRed, vecGreen, vecBlue;

};



#endif // IMAGEARRAY_H
