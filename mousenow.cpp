#ifndef MOUSENOW
#define MOUSENOW

// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QDebug>
#include <QRgb>
#include <QColor>
#include <QVector>
#include <QCursor>

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    /*bool isMouseEvent =
            (event->type() == QEvent::MouseButtonPress) ||
            (event->type() == QEvent::MouseButtonRelease) ||
            (event->type() == QEvent::MouseMove)||
            (event->type() == QEvent::MouseButtonDblClick) ||
            (event->type() == QEvent::MouseTrackingChange);*/
    bool canDraw;
    if(watched == ui->graphicsView && event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = (QMouseEvent*) event;
        qDebug() << "clicked on the image at " << mouseEvent->pos().x() << mouseEvent->pos().y();
        if(finishScissor){
            if(lastx >= 0){
                lastx = startx; lasty = starty;
                if(!undoDisabled){
                    startx = endx; starty = endy;
                }
            }else{
                startx = mouseEvent->pos().x() -5; starty = mouseEvent->pos().y() -5;
            }
            finishScissor = false;
            imgscene->clear();
            imgscene->addPixmap(QPixmap::fromImage(*mkimage));
            ui->graphicsView->setScene(imgscene);
            ui->graphicsView->show();
        }else{
            endx = mouseEvent->pos().x() -5;
            endy = mouseEvent->pos().y() -5;
            canDraw =
                    (startx > 0 && startx < image->width()) &&
                    (starty > 0 && starty < image->height()) &&
                    (endx > 0 && endx < image->width()) &&
                    (endy > 0 && endy < image->height());
            if(canDraw){
                tempPath(startx, starty, endx, endy, false);
                finishScissor = true;
                undoDisabled = true;
            }
        }
    }else if(watched == imgscene){
        QPoint mousePos = mapFromGlobal(QCursor::pos());
        mousex = mousePos.x() -5;
        mousey = mousePos.y() - 50;
        ui->statusBar->showMessage(QString("%1, %2").arg(mousex).arg(mousey));
        canDraw =
                (startx > 0 && startx < image->width()) &&
                (starty > 0 && starty < image->height()) &&
                (mousex > 0 && mousex < image->width()) &&
                (mousey > 0 && mousey < image->height()) &&
                (endx > 0 && endx < image->width()) &&
                (endy > 0 && endy < image->height());
        if(canDraw && !finishScissor){
            *tempImage = mkimage->copy();
            tempPath(endx, endy, mousex, mousey, true);
        }
    }
    return false;
}

void MainWindow::drawPix(int x, int y)
{
    QColor pixclr = QColor::fromRgb(66,  66,  66);
    this->mousex = x; this->mousey = y;
    for(int h = -20; h< 20; h++){
        for(int w = -21; w<22; w++){
            mkimage->setPixelColor(x+w/3, y+h, pixclr);
        }
    }
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

void MainWindow::drawEdge()
{
    QColor edgeColor = QColor::fromRgb(255,  0,  0); // red
    QColor borderColor = QColor::fromRgb(0,  255,  0); // green
    int shouldTake = 1; bool canSetEdge = false; bool canSetBorder;
    qDebug() << "in drawEdge";
    for(int h = 0; h < image->height(); h++){
        for(int w = 0; w < image->width(); w++){
            if (shouldTake < imgarray.vecEdge.count()){
                canSetEdge = imgarray.vecEdge.at(shouldTake);
                canSetBorder = imgarray.vecBorder.at(shouldTake);
                if (canSetEdge){
                    mkimage->setPixelColor(w, h, edgeColor);
                }
                if (canSetBorder){
                    mkimage->setPixelColor(w, h, borderColor);
                }
                shouldTake++;
            }
        }
    }
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

void MainWindow::drawTempEdge()
{
    QColor edgeColor = QColor::fromRgb(255,  0,  0); // red
    QColor borderColor = QColor::fromRgb(0,  255,  0); // green
    int shouldTake = 1; bool canSetEdge = false; bool canSetBorder;
    for(int h = 0; h < image->height(); h++){
        for(int w = 0; w < image->width(); w++){
            if (shouldTake < imgarray.vecEdge.count()){
                canSetEdge = imgarray.vecTempEdge.at(shouldTake); imgarray.vecTempEdge[shouldTake] = false;
                canSetBorder = imgarray.vecTempBorder.at(shouldTake); imgarray.vecTempBorder[shouldTake] = false;
                if (canSetEdge){
                    tempImage->setPixelColor(w, h, edgeColor);
                }
                if (canSetBorder){
                    tempImage->setPixelColor(w, h, borderColor);
                }
                shouldTake++;
            }
        }
    }
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*tempImage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

void MainWindow::toEdgeVec()
{
    for(int h = 20; h < 180; h++){
        for(int w = -20; w< 20; w++){
            imgarray.vecEdge[h* imgarray.getWidth() + h + w]  = true;
        }
    }
    drawEdge();
}

bool MainWindow::genBorder(bool temp = false)
{
    bool isBorder = false; int loc = 0; int pixnum;
    pixnum = this->imgarray.vecBorder.count();
    for(int index = 0; index < pixnum; index++){
        if (!temp && imgarray.vecEdge.at(index)){
            for(int w = -5; w < 6; w++){
                for (int h = -5; h < 6; h ++){
                    loc = index + w + h * this->imgarray.getWidth();
                    if(loc <= 0 || loc > pixnum){continue;}
                    isBorder = (!imgarray.vecEdge.at(loc)) && (!imgarray.vecBorder.at(loc));
                    if(isBorder){
                        imgarray.vecBorder[loc - 1] = true;
                    }
                }
            }
        } else if (temp && imgarray.vecTempEdge.at(index)){
            for(int w = -5; w < 6; w++){
                for (int h = -5; h < 6; h ++){
                    loc = index + w + h * this->imgarray.getWidth();
                    if(loc <= 0 || loc > pixnum){continue;}
                    isBorder = (!imgarray.vecTempEdge.at(loc)) && (!imgarray.vecTempBorder.at(loc));
                    if(isBorder){
                        imgarray.vecTempBorder[loc - 1] = true;
                    }
                }
            }
        }
    }
    return true;
}

void MainWindow::tempPath(int spx, int spy, int epx, int epy, bool realtime = false)
{
    int loc = 0;
    if(spx >= epx){
        if(spy >= epy){
            //l->u, r->l
            for(int x = 0; x <= spx - epx; x++){
                loc = imgarray.vecloc(epx + x, spy);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
            for(int y = 0; y <= spy - epy; y++){
                loc = imgarray.vecloc(epx, epy + y);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
        }else{
            //l->u, r->l
            for(int x = 0; x <= spx - epx; x++){
                loc = imgarray.vecloc(epx + x, epy);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
            for(int y = 0; y <= epy - spy; y++){
                loc = imgarray.vecloc(spx, spy + y);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
        }
    }else{
        if(spy >= epy){
            //l->u, l->r
            for(int x = 0; x <= epx - spx; x++){
                loc = imgarray.vecloc(spx + x, epy);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
            for(int y = 0; y <= spy - epy; y++){
                loc = imgarray.vecloc(spx, epy + y);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
        }else{
            //u->l, l->r
            for(int x = 0; x <= epx - spx; x++){
                loc = imgarray.vecloc(spx + x, spy);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
            for(int y = 0; y <= epy - spy; y++){
                loc = imgarray.vecloc(epx, spy + y);
                if(realtime){
                    imgarray.vecTempEdge[loc] = true;
                }else{
                    imgarray.vecEdge[loc] = true;
                }
            }
        }
    }
    if(genBorder(realtime)){
        if(realtime){
            drawTempEdge();
        }else{
            drawEdge();
        }
    }



}


#endif
