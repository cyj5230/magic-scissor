#ifndef MAINWINDOW
#define MAINWINDOW

// include basic qt header files
#include "mainwindow.h"
#include "ui_mainwindow.h"

// include user-defined cpp files
#include "ismenubar.cpp"
#include "mousenow.cpp"

#include "imagearray.h"

// include qt libs
#include <QMouseEvent>
#include <QPoint>
#include <QEvent>
#include <QCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initialization
    ui->setupUi(this);
    ui->centralWidget->adjustSize();
    ui->graphicsView->resize(ui->centralWidget->size());
    ui->centralWidget->setMouseTracking(true);
    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->installEventFilter(this);

    this->setWindowTitle("Intelligent Scissor");
    this->image = new QImage();
    this->rawImage = new QImage();
    // QT will create on_actionX_triggered function automatically, and connect it with QAction::triggered()
    // This autoconnection will be created by declaring and implementing a slot with the name that follows the below rules:
    //      void on_<widget name="">_<signal name="">(<signal parameters="">);

}

MainWindow::~MainWindow()
{
    delete ui;
}

#endif // MAINWINDOW
