#ifndef IMAGEARRAY_H
#define IMAGEARRAY_H

#include <QPixmap>
#include <QVector>
#include <QRgb>

// currently only deal with rgb images

class imArray
{
public:
    QVector<bool> vecEdge, vecBorder;
    //void edgeline(QImage *image);
    //void edgeborder(QImage *image);
    // input functions
    void setImage(QImage *image){
        this->img = image;
        this->width = (int)image->width();
        this->height = (int)image->height();
        for(int haxis = 0; haxis < this->height; haxis++){
            QRgb* line = (QRgb*)image->scanLine(haxis);
            for(int waxis = 0; waxis < this->width; waxis++){
                QRgb pixelInfo = line[waxis];
                this->vecBlue.append(qBlue(pixelInfo));
                this->vecGreen.append(qGreen(pixelInfo));
                this->vecRed.append(qRed(pixelInfo));
                this->vecEdge.append(false);
                this->vecBorder.append(false);
            }
        }
    }
    void setEdge(){
        vecEdge.replace(66, true);
    }

    // output functions
    int getHeight(){return(this->height);}
    int getWidth(){return(this->width);}
    int getRed(int loc){return vecRed.takeAt(loc);}
    int getGreen(int loc){return vecGreen.takeAt(loc);}
    int getBlue(int loc){return vecBlue.takeAt(loc);}

private:
    QImage *img ;
    int width, height;
    QVector<int> vecRed, vecGreen, vecBlue;
};

/*
void imArray::edgeline(QImage *image)
{

}

void imArray::edgeborder(QImage *image)
{

}
*/

#endif // IMAGEARRAY_H
