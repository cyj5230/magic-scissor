#include <QMouseEvent>
#include <QPoint>
#include <QString>

// this cpp source file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW_H
#include "mainwindow.cpp"
#endif

#ifndef IMAGEVIEWER
#include "imageviewer.cpp"
#endif

void MainWindow::mouseInfo()
{
    ui->statusBar->showMessage(mouseMsg);
}

