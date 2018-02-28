// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QDebug>

// Rewrite on_actionX_triggered slot functions

// File operations

void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                ".",
                "Image Files (*.bmp *.jpg *png);;All Files(*.*)");
   imgFileName = fileName;
    if (fileName != ""){
        if (image->load(fileName)){
            rawImage->load(fileName);
            mkimage->load(fileName);
            imgarray.setImage(image);
            imgscene->clear();
            imgscene->addPixmap(QPixmap::fromImage(*image));
            imgscene->installEventFilter(this);
            ui->graphicsView->setScene(imgscene);
            ui->graphicsView->resize(image->width() + 10, image->height() + 10);
            ui->graphicsView->show();
            initNodeBuffer(nodes, image);
        }
    }
}

void MainWindow::on_actionCloseImage_triggered(){
    imgscene->clear();
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->show();
}

// Size operations

void MainWindow::on_actionSize_x1_triggered(){
    imageSizeChange(1.0);
}

void MainWindow::on_actionSize_x2_triggered()
{
    imageSizeChange(2.0);
}

void MainWindow::imageSizeChange(double scaleFactor)
{
    if((double)scaleFactor != 1.0){
        qreal imwidth = rawImage->width(); qreal imheight = rawImage->height();
        *image = rawImage->scaled(imwidth * scaleFactor, imheight * scaleFactor);
        *mkimage = rawImage->scaled(imwidth * scaleFactor, imheight * scaleFactor);
        imgarray.setImage(image);
        imgscene->clear();
        imgscene->addPixmap(QPixmap::fromImage(*image));
        ui->graphicsView->setScene(imgscene);
        ui->graphicsView->resize(image->width() + 10, image->height() + 10);
        ui->graphicsView->show();
    }else{
        imgscene->clear();
        imgscene->addPixmap(QPixmap::fromImage(*rawImage));
        image->load(imgFileName);
        mkimage->load(imgFileName);
        imgarray.setImage(image);
        ui->graphicsView->setScene(imgscene);
        ui->graphicsView->resize(rawImage->width() + 10, rawImage->height() + 10);
        ui->graphicsView->show();
    }

}
void MainWindow::on_actionPixel_triggered()
{
    QColor pixInfo = mkimage->pixel(20,20);
    QColor pixclr = QColor::fromRgb(66,  66,  66);
    qDebug() << pixInfo.red() << pixInfo.green() << pixInfo.blue();
    mkimage->setPixelColor(20, 20, pixclr);
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    pixInfo = mkimage->pixel(20,20);
    qDebug() << pixInfo.red() << pixInfo.green() << pixInfo.blue();
    /*
    QColor pixInfo = image->pixel(0,0);
    int imBlue = pixInfo.blue();
    QString statusMessage = QString("%1").arg(imBlue);
    ui->statusBar->showMessage(statusMessage);
    MainWindow::toEdgeVec();
    */
}

void MainWindow::on_actionLiveWire_triggered()
{

}

void MainWindow::on_actiontest_triggered()
{
    int pixx = 264, pixy =123;
    QColor pixInfo = mkimage->pixel(pixx,pixy);
    QColor pixclr = QColor::fromRgb(66,  66,  66);
    qDebug() << pixInfo.red() << pixInfo.green() << pixInfo.blue();
    mkimage->setPixelColor(pixx, pixy, pixclr);
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*mkimage));
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    pixInfo = mkimage->pixel(pixx,pixy);
    qDebug() << pixInfo.red() << pixInfo.green() << pixInfo.blue();
}

void MainWindow::on_actionCost_Graph_triggered()
{
    int graphWidth = image->width() * 3;
    int graphHeight = image->height() * 3;
    *costGraph = QPixmap(graphWidth, graphHeight).toImage();

    makeCostGraph(costGraph, nodes, image->width(), image->height());

    //display costgraph
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*costGraph));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    ui->graphicsView->show();
}

void MainWindow::on_actionPixel_Node_triggered()
{
    int graphWidth = image->width() * 3;
    int graphHeight = image->height() * 3;
    *pixelNodes = QPixmap(graphWidth, graphHeight).toImage();

    makePixelNodes(pixelNodes, image->width(), image->height());

    //display pixel nodes
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*pixelNodes));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(graphWidth + 10, graphHeight + 10);
    ui->graphicsView->show();
}

