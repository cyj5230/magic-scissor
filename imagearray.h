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
    QVarLengthArray<bool> vecInner;
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
        this->pixnum = this->vecEdge.count();
        //qDebug() << "Image Size: " << this->width << "x" << this->height;
        //qDebug() << "has alpha channel:" <<image->hasAlphaChannel() << "image format:" << image->format();
        //qDebug() << "pixel number:" << vecEdge.count() << vecBorder.count();
    }
    bool resetImage(){
        if(!vecEdge.isEmpty()){
            for(int index = 0; index < this->vecEdge.count(); index++){
                this->vecEdge[index]       = false;
                this->vecBorder[index]     = false;
                this->vecTempEdge[index]   = false;
                this->vecTempBorder[index] = false;
                this->vecInner[index] = true;
            }
        }
        //only for debug
        return false;
    }
    bool findInner(){
        if(pixnum == 0){return false;}
        bool finish = false;
        bool isEdge, isOuter;
        qDebug() << pixnum;
        for(int index = 0; index < pixnum; index++){
            vecInner.append(true);
        }
        while(!finish){
            finish = true;
            for(int w = 0; w < width; w++){
                for(int h = 0; h < height; h++){
                    isEdge =
                            w - 1 <= 0 || w + 1 >= this->width ||
                            h - 1 <= 0 || h + 1 >= this->height;
                    if(isEdge){vecInner[vecloc(w,h)] = false; continue;}
                    isOuter =
                             vecEdge[ vecloc(w,h) ]  == false &&
                            (vecInner[vecloc(w-1,h)] == false ||
                             vecInner[vecloc(w,h-1)] == false ||
                             vecInner[vecloc(w+1,h)] == false ||
                             vecInner[vecloc(w,h+1)] == false) ;
                    if(isOuter){
                        if(vecInner[vecloc(w,h)] == true){
                            vecInner[vecloc(w,h)] = false;
                            finish = false;
                        }
                    }

                }
            }
        }
        return true;
    }

    // output functions
    int getHeight(){return(this->height);}
    int getWidth(){return(this->width);}
    int getRed(int loc){
        if(loc >= 0 && loc < width * height)
            return vecRed.at(loc);
        else
            return 0;
    }
    int getGreen(int loc){
        if(loc >= 0 && loc < width * height)
            return vecGreen.at(loc);
        else
            return 0;
    }
    int getBlue(int loc){
        if(loc >= 0 && loc < width * height)
            return vecBlue.at(loc);
        else
            return 0;
    }

    int getPixnum(){
        return pixnum;
    }

    // change cordinator to index
    int vecloc(int w, int h){return h * this->width + w;}

private:
    int width, height;
    int pixnum = 0;
    QVarLengthArray<int> vecRed, vecGreen, vecBlue;
};



#endif // IMAGEARRAY_H
