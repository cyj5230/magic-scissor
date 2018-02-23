#ifndef MOUSENOW
#define MOUSENOW

// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QDebug>
#include <QRgb>

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
        QPoint mousePos = mouseEvent->pos();
        ui->statusBar->showMessage(QString("%1").arg(mousePos.x()));
        if(event->type() == QEvent::MouseButtonPress){
            drawPix(mousePos.x(), mousePos.y());
        }
    }
    return false;
}

void MainWindow::drawPix(int x, int y)
{
    this->mousex = x; this->mousey = y;
    for(int h = -50; h< 50; h++){
        for(int w = -50; w<50; w++){
            image->setPixel(x+w, y+h, Qt::red);
        }
    }
    image->setPixel(x, y ,Qt::red);
    QPixmap imgarea = QPixmap::fromImage(*image);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(imgarea);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
}

#endif
