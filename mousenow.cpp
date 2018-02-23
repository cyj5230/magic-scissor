#ifndef MOUSENOW
#define MOUSENOW

// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QDebug>
#include <QRgb>
#include <QVector>

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    bool isMouseEvent =
            (event->type() == QEvent::MouseButtonPress) ||
            (event->type() == QEvent::MouseButtonRelease) ||
            (event->type() == QEvent::MouseMove)||
            (event->type() == QEvent::MouseButtonDblClick) ||
            (event->type() == QEvent::MouseTrackingChange);
    if(watched == ui->graphicsView && isMouseEvent){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QPoint mousePos = mapFromParent( mouseEvent->pos());
        ui->statusBar->showMessage(QString("%1").arg(mousePos.x()));
        switch (event->type()) {
        case QEvent::MouseButtonPress:
            if(lastx >= 0){
                lastx = startx; lasty = starty;
                if(!undoDisabled){
                    startx = endx; starty = endy;
                }
            }else{
                startx = mousePos.x(); starty = mousePos.y();
            }
            drawPix(mousePos.x(), mousePos.y());
            break;
        case QEvent::MouseMove:
            mousex = mousePos.x(); mousey = mousePos.y();
            break;
        case QEvent::MouseButtonRelease:
            endx = mousePos.x(); endy = mousePos.y();
            break;
        case QEvent::MouseButtonDblClick:
            undoDisabled = true;
            break;
        default:
            break;
        }
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
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(scene);
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
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

void MainWindow::toEdgeVec()
{
    for(int h = 20; h < 180; h++){
        for(int w = -20; w< 20; w++){
            imgarray.vecEdge.replace(h* imgarray.getWidth() + h + w, true);
        }
    }
    drawEdge();
}



#endif
