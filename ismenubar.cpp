// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

// Rewrite on_actionX_triggered slot functions

// File operations

void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                ".",
                "Image Files (*.bmp *.jpg *png);;All Files(*.*)");
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

void MainWindow::on_actionLiveWire_triggered()
{

}



