#ifndef MOUSENOW
#define MOUSENOW

// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QDebug>
#include <QRgb>
#include <QVector>
#include <QCursor>

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    bool isMouseEvent =
            (event->type() == QEvent::MouseButtonPress) ||
            (event->type() == QEvent::MouseButtonRelease) ||
            (event->type() == QEvent::MouseMove)||
            (event->type() == QEvent::MouseButtonDblClick) ||
            (event->type() == QEvent::MouseTrackingChange);
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
    QPoint mousePos = mouseEvent->pos();
    if(watched == ui->graphicsView && isMouseEvent){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        qDebug() << "clicked on the image at " << mouseEvent->pos().x() << mouseEvent->pos().y();
        if(finishScissor){
            if(lastx >= 0){
                lastx = startx; lasty = starty;
                if(!undoDisabled){
                    startx = endx; starty = endy;
                }
            }else{
                startx = mousePos.x(); starty = mousePos.y();
            }
        }else{
            endx = mousePos.x(); endy = mousePos.y();
            tempPath(startx, starty, endx, endy);
            undoDisabled = true;
        }
    }
    if(watched == imgscene){
        ui->statusBar->showMessage(QString("%1, %2").arg(mousePos.x()).arg(mousePos.y()));
        mousex = mousePos.x(); mousey = mousePos.y();
    }
    return false;
}

void MainWindow::drawPix(int x, int y)
{
    this->mousex = x; this->mousey = y;
    for(int h = -20; h< 20; h++){
        for(int w = -20; w<20; w++){
            mkimage->setPixel(x+w, y+h, Qt::red);
        }
    }
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

void MainWindow::drawEdge()
{
    int shouldTake = 1; bool canSet = false;
    for(int h = 0; h < image->height(); h++){
        for(int w = 0; w < image->width(); w++){
            if (shouldTake < imgarray.vecEdge.count()){
                canSet = imgarray.vecEdge.takeAt(shouldTake++);
                if (canSet){
                    mkimage->setPixel(w, h, Qt::blue);
                }
            }
        }
    }
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

void MainWindow::toEdgeVec()
{
    for(int h = 20; h < 180; h++){
        for(int w = -20; w< 20; w++){
            imgarray.vecEdge[h* imgarray.getWidth() + h + w]  = true;
            //imgarray.vecEdge.replace(h* imgarray.getWidth() + h + w, true);
        }
    }
    drawEdge();
}

void MainWindow::tempPath(int spx, int spy, int epx, int epy)
{
    int startAt = (spy + 1) * image->width() + spx +1;
    int infAt = (spy + 1) * image->width() + epx + 1;
    int endAt = (epy + 1) * image->width() + epy + 1;
    for( int w = startAt; w <= infAt; w ++){
        imgarray.vecEdge[(spy + 1) * image->width() + w] = true;
    }
    for( int h = spy; h <= epy; h++ ){
        imgarray.vecEdge[epx + 1 + h * image->width()] = true;
    }
    drawEdge();
}


#endif
