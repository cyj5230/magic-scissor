#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Initialization
    ui->setupUi(this);
    this->setWindowTitle("Intelligent Scissor");

    this->image = new QImage();
    this->rawImage = new QImage();
    this->scaleFactor = 1.0;

    // QT will create on_actionX_triggered function automatically, and connect it with QAction::triggered()
    // This autoconnection will be created by declaring and implementing a slot with the name that follows the below rules:
    //      void on_<widget name="">_<signal name="">(<signal parameters="">);

    // StatusBar
}


MainWindow::~MainWindow()
{
    delete ui;
}

// Rewrite on_actionX_triggered function

// File operations

void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                ".",
                "Image files (*.bmp, *.jpg *png);;All files(*.*)");
    if (fileName != ""){
        if (image->load(fileName)){
            rawImage->load(fileName);
            QGraphicsScene *scene = new QGraphicsScene;
            scene->addPixmap(QPixmap::fromImage(*image));
            ui->graphicsView->setScene(scene);
            ui->graphicsView->resize(image->width() + 10, image->height() + 10);
            ui->graphicsView->show();
        }
    }
}

void MainWindow::on_actionCloseImage_triggered(){
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

// Size operations

void MainWindow::on_actionSize_x1_triggered(){
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*rawImage));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(rawImage->width() + 10, rawImage->height() + 10);
    ui->graphicsView->show();
}

void MainWindow::on_actionSize_x2_triggered()
{
    qreal imwidth = rawImage->width(); qreal imheight = rawImage->height();
    *image = rawImage->scaled(imwidth * 2.0, imheight * 2.0);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    ui->graphicsView->show();
}

void MainWindow::on_actionPixel_triggered()
{
    QColor pixInfo = image->pixel(0,0);
    int imBlue = pixInfo.blue();
    QString statusMessage = QString("%1").arg(imBlue);
    ui->statusBar->showMessage(statusMessage);
}

