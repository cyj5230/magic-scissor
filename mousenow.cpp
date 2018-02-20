#ifndef MOUSENOW
#define MOUSENOW

// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->graphicsView && event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QString mousePos = QString("%1, %2").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y());
        ui->statusBar->showMessage(mousePos);
    }
    return false;
}

#endif
