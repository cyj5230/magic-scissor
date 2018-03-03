// This file should be accessed from mainwindow.cpp
#ifndef MAINWINDOW
#include "mainwindow.cpp"
#endif

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QMatrix3x3>

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
            initNodeBuffer();
        }
    }
}

void MainWindow::on_actionCloseImage_triggered(){
    imgscene->clear();
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->show();
    imgarray.resetImage();
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
    if(image->isNull()){
        QMessageBox msgBox;
        msgBox.setText("There is no image!");
        msgBox.exec();
        return;
    }
    int graphWidth = image->width() * 3;
    int graphHeight = image->height() * 3;
    *debugGraph = QPixmap(graphWidth, graphHeight).toImage();

    makeCostGraph(image->width(), image->height());

    //display costgraph
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*debugGraph));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(graphWidth + 10, graphHeight + 10);
    ui->graphicsView->show();

    //to be done: disable the mouse
}

void MainWindow::on_actionPath_Tree_triggered()
{
    if(image->isNull()){
        QMessageBox msgBox;
        msgBox.setText("There is no image!");
        msgBox.exec();
        return;
    }
    int graphWidth = image->width() * 3;
    int graphHeight = image->height() * 3;
    *debugGraph = QPixmap(graphWidth, graphHeight).toImage();

    bool ok = false;
    int numNodes = image->width() * image->height();
    int expand = QInputDialog::getInt(
                this, tr("Intelligent Scissor"),
                tr("Please enter the number of expanded nodes"), numNodes,
                0, numNodes, numNodes/10, &ok);
    if(ok)
        makePathTree(image->width(), image->height(), expand);
    else{
        QMessageBox msgBox;
        msgBox.setText("There is no expand number!");
        msgBox.exec();
        return;
    }

    //display costgraph
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*debugGraph));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(graphWidth + 10, graphHeight + 10);
    ui->graphicsView->show();

    //to be done: disable the mouse
}

void MainWindow::on_actionMin_Path_triggered()
{
    if(image->isNull()){
        QMessageBox msgBox;
        msgBox.setText("There is no image!");
        msgBox.exec();
        return;
    }
    int graphWidth = image->width() * 3;
    int graphHeight = image->height() * 3;
    *debugGraph = QPixmap(graphWidth, graphHeight).toImage();

    makeMinPath(image->width(), image->height());

    //display pixel nodes
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*debugGraph));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(graphWidth + 10, graphHeight + 10);
    ui->graphicsView->show();

    //to be done: enable the mouse
}

void MainWindow::on_actionSave_Contour_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF"));
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        if(!(mkimage->save(filename)))
        {
            QMessageBox::information(this,
                tr("Failed to save the image"),
                tr("Failed to save the image!"));
            return;
        }
    }
}

void MainWindow::on_actionSave_Mask_triggered()
{
    QImage *maskImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    if(finishScissor && imgarray.findInner()){
        for(int w = 0; w < imgarray.getWidth(); w++){
            for(int h = 0; h < imgarray.getHeight(); h++){
                if(imgarray.vecInner.at(imgarray.vecloc(w,h))){
                    QColor inclr = QColor::fromRgb(imgarray.getRed(imgarray.vecloc(w,h)),
                                                   imgarray.getGreen(imgarray.vecloc(w,h)),
                                                   imgarray.getBlue(imgarray.vecloc(w,h)));
                    maskImage->setPixelColor(w, h, inclr);
                }else{
                    maskImage->setPixelColor(w, h, QColor(0,0,0,0));
                }
            }
        }
    }
//    //*tempImage = mkimage->createMaskFromColor(QColor(0,0,0).rgb(), Qt::MaskOutColor);
//    imgscene->clear();
//    imgscene->addPixmap(QPixmap::fromImage(*maskImage));
//    ui->graphicsView->setScene(imgscene);
//    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF"));
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        if(!(maskImage->save(filename)))
        {
            QMessageBox::information(this,
                tr("Failed to save the image"),
                tr("Failed to save the image!"));
            return;
        }
    }
}

void MainWindow::on_action3_x_3_triggered()
{
    if(image->isNull())
        return;

    QImage blur = QPixmap::fromImage(*image).toImage();

    QMatrix3x3 kernel;
    kernel(0, 0) = 1; kernel(0, 1) = 2; kernel(0, 2) = 1;
    kernel(1, 0) = 2; kernel(1, 1) = 4; kernel(1, 2) = 2;
    kernel(2, 0) = 1; kernel(2, 1) = 2; kernel(2, 2) = 1;
    float kernel_sum = 16.0;


    for(int i=1; i<image->width()-1; i++)
    {
        for(int j=1; j<image->height()-1; j++)
        {
            float red = 0, green = 0, blue = 0;

            // *****************************************************
            red =
                    kernel(0, 0) * qRed(image->pixel(i+1, j+1)) +
                    kernel(0, 1) * qRed(image->pixel(i, j+1)) +
                    kernel(0, 2) * qRed(image->pixel(i-1, j+1)) +

                    kernel(1, 0) * qRed(image->pixel(i+1, j)) +
                    kernel(1, 1) * qRed(image->pixel(i, j)) +
                    kernel(1, 2) * qRed(image->pixel(i-1, j)) +

                    kernel(2, 0) * qRed(image->pixel(i+1, j-1)) +
                    kernel(2, 1) * qRed(image->pixel(i, j-1)) +
                    kernel(2, 2) * qRed(image->pixel(i-1, j-1));

            // *****************************************************
            green =
                    kernel(0, 0) * qGreen(image->pixel(i+1, j+1)) +
                    kernel(0, 1) * qGreen(image->pixel(i, j+1)) +
                    kernel(0, 2) * qGreen(image->pixel(i-1, j+1)) +

                    kernel(1, 0) * qGreen(image->pixel(i+1, j)) +
                    kernel(1, 1) * qGreen(image->pixel(i, j)) +
                    kernel(1, 2) * qGreen(image->pixel(i-1, j)) +

                    kernel(2, 0) * qGreen(image->pixel(i+1, j-1)) +
                    kernel(2, 1) * qGreen(image->pixel(i, j-1)) +
                    kernel(2, 2) * qGreen(image->pixel(i-1, j-1));

            // *****************************************************
            blue =
                    kernel(0, 0) * qBlue(image->pixel(i+1, j+1)) +
                    kernel(0, 1) * qBlue(image->pixel(i, j+1)) +
                    kernel(0, 2) * qBlue(image->pixel(i-1, j+1)) +

                    kernel(1, 0) * qBlue(image->pixel(i+1, j)) +
                    kernel(1, 1) * qBlue(image->pixel(i, j)) +
                    kernel(1, 2) * qBlue(image->pixel(i-1, j)) +

                    kernel(2, 0) * qBlue(image->pixel(i+1, j-1)) +
                    kernel(2, 1) * qBlue(image->pixel(i, j-1)) +
                    kernel(2, 2) * qBlue(image->pixel(i-1, j-1));

            blur.setPixel(i,j, qRgb(red/kernel_sum, green/kernel_sum, blue/kernel_sum));

        }
    }

    *image = blur;
    imgarray.setImage(image);
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*image));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    ui->graphicsView->show();
    initNodeBuffer();
}

void MainWindow::on_action5_x_5_triggered()
{
    if(image->isNull())
        return;

    QImage blur = QPixmap::fromImage(*image).toImage();

    int** kernel = new int*[5];
    for(int k = 0; k < 5; k++){
        kernel[k] = new int[5];
    }
    kernel[0][0] = kernel[0][4] = kernel[4][0] = kernel[4][4] = 2;
    kernel[0][1] = kernel[0][3] = kernel[1][0] = kernel[1][4] = 4;
    kernel[3][0] = kernel[3][4] = kernel[4][1] = kernel[4][3] = 4;
    kernel[0][2] = kernel[2][0] = kernel[2][4] = kernel[4][2] = 5;
    kernel[1][1] = kernel[1][3] = kernel[3][1] = kernel[3][3] = 9;
    kernel[1][2] = kernel[2][1] = kernel[2][3] = kernel[3][2] = 12;
    kernel[2][2] = 15;
    float kernel_sum = 159.0;


    for(int i=2; i<image->width()-2; i++)
    {
        for(int j=2; j<image->height()-2; j++)
        {
            float red = 0, green = 0, blue = 0;

            // *****************************************************
            red =
                    kernel[0][0] * qRed(image->pixel(i-2, j-2)) +
                    kernel[0][1] * qRed(image->pixel(i-1, j-2)) +
                    kernel[0][2] * qRed(image->pixel(i, j-2)) +
                    kernel[0][3] * qRed(image->pixel(i+1, j-2)) +
                    kernel[0][4] * qRed(image->pixel(i+2, j-2)) +

                    kernel[1][0] * qRed(image->pixel(i-2, j-1)) +
                    kernel[1][1] * qRed(image->pixel(i-1, j-1)) +
                    kernel[1][2] * qRed(image->pixel(i, j-1)) +
                    kernel[1][3] * qRed(image->pixel(i+1, j-1)) +
                    kernel[1][4] * qRed(image->pixel(i+2, j-1)) +

                    kernel[2][0] * qRed(image->pixel(i-2, j)) +
                    kernel[2][1] * qRed(image->pixel(i-1, j)) +
                    kernel[2][2] * qRed(image->pixel(i, j)) +
                    kernel[2][3] * qRed(image->pixel(i+1, j)) +
                    kernel[2][4] * qRed(image->pixel(i+2, j)) +

                    kernel[3][0] * qRed(image->pixel(i-2, j+1)) +
                    kernel[3][1] * qRed(image->pixel(i-1, j+1)) +
                    kernel[3][2] * qRed(image->pixel(i, j+1)) +
                    kernel[3][3] * qRed(image->pixel(i+1, j+1)) +
                    kernel[3][4] * qRed(image->pixel(i+2, j+1)) +

                    kernel[4][0] * qRed(image->pixel(i-2, j+2)) +
                    kernel[4][1] * qRed(image->pixel(i-1, j+2)) +
                    kernel[4][2] * qRed(image->pixel(i, j+2)) +
                    kernel[4][3] * qRed(image->pixel(i+1, j+2)) +
                    kernel[4][4] * qRed(image->pixel(i+2, j+2));

            // *****************************************************
            green =
                    kernel[0][0] * qGreen(image->pixel(i-2, j-2)) +
                    kernel[0][1] * qGreen(image->pixel(i-1, j-2)) +
                    kernel[0][2] * qGreen(image->pixel(i, j-2)) +
                    kernel[0][3] * qGreen(image->pixel(i+1, j-2)) +
                    kernel[0][4] * qGreen(image->pixel(i+2, j-2)) +

                    kernel[1][0] * qGreen(image->pixel(i-2, j-1)) +
                    kernel[1][1] * qGreen(image->pixel(i-1, j-1)) +
                    kernel[1][2] * qGreen(image->pixel(i, j-1)) +
                    kernel[1][3] * qGreen(image->pixel(i+1, j-1)) +
                    kernel[1][4] * qGreen(image->pixel(i+2, j-1)) +

                    kernel[2][0] * qGreen(image->pixel(i-2, j)) +
                    kernel[2][1] * qGreen(image->pixel(i-1, j)) +
                    kernel[2][2] * qGreen(image->pixel(i, j)) +
                    kernel[2][3] * qGreen(image->pixel(i+1, j)) +
                    kernel[2][4] * qGreen(image->pixel(i+2, j)) +

                    kernel[3][0] * qGreen(image->pixel(i-2, j+1)) +
                    kernel[3][1] * qGreen(image->pixel(i-1, j+1)) +
                    kernel[3][2] * qGreen(image->pixel(i, j+1)) +
                    kernel[3][3] * qGreen(image->pixel(i+1, j+1)) +
                    kernel[3][4] * qGreen(image->pixel(i+2, j+1)) +

                    kernel[4][0] * qGreen(image->pixel(i-2, j+2)) +
                    kernel[4][1] * qGreen(image->pixel(i-1, j+2)) +
                    kernel[4][2] * qGreen(image->pixel(i, j+2)) +
                    kernel[4][3] * qGreen(image->pixel(i+1, j+2)) +
                    kernel[4][4] * qGreen(image->pixel(i+2, j+2));

            // *****************************************************
            blue =
                    kernel[0][0] * qBlue(image->pixel(i-2, j-2)) +
                    kernel[0][1] * qBlue(image->pixel(i-1, j-2)) +
                    kernel[0][2] * qBlue(image->pixel(i, j-2)) +
                    kernel[0][3] * qBlue(image->pixel(i+1, j-2)) +
                    kernel[0][4] * qBlue(image->pixel(i+2, j-2)) +

                    kernel[1][0] * qBlue(image->pixel(i-2, j-1)) +
                    kernel[1][1] * qBlue(image->pixel(i-1, j-1)) +
                    kernel[1][2] * qBlue(image->pixel(i, j-1)) +
                    kernel[1][3] * qBlue(image->pixel(i+1, j-1)) +
                    kernel[1][4] * qBlue(image->pixel(i+2, j-1)) +

                    kernel[2][0] * qBlue(image->pixel(i-2, j)) +
                    kernel[2][1] * qBlue(image->pixel(i-1, j)) +
                    kernel[2][2] * qBlue(image->pixel(i, j)) +
                    kernel[2][3] * qBlue(image->pixel(i+1, j)) +
                    kernel[2][4] * qBlue(image->pixel(i+2, j)) +

                    kernel[3][0] * qBlue(image->pixel(i-2, j+1)) +
                    kernel[3][1] * qBlue(image->pixel(i-1, j+1)) +
                    kernel[3][2] * qBlue(image->pixel(i, j+1)) +
                    kernel[3][3] * qBlue(image->pixel(i+1, j+1)) +
                    kernel[3][4] * qBlue(image->pixel(i+2, j+1)) +

                    kernel[4][0] * qBlue(image->pixel(i-2, j+2)) +
                    kernel[4][1] * qBlue(image->pixel(i-1, j+2)) +
                    kernel[4][2] * qBlue(image->pixel(i, j+2)) +
                    kernel[4][3] * qBlue(image->pixel(i+1, j+2)) +
                    kernel[4][4] * qBlue(image->pixel(i+2, j+2));

            blur.setPixel(i,j, qRgb(red/kernel_sum, green/kernel_sum, blue/kernel_sum));

        }
    }

    for(int l = 0; l < 5; l++){
        delete [] kernel[l];
    }
    delete [] kernel;

    *image = blur;
    imgarray.setImage(image);
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*image));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(image->width() + 10, image->height() + 10);
    ui->graphicsView->show();
    initNodeBuffer();
}

void MainWindow::on_actionPixel_Node_triggered()
{
    if(image->isNull()){
        QMessageBox msgBox;
        msgBox.setText("There is no image!");
        msgBox.exec();
        return;
    }
    int graphWidth = image->width() * 3;
    int graphHeight = image->height() * 3;
    *debugGraph = QPixmap(graphWidth, graphHeight).toImage();

    makePixelNodes(image->width(), image->height());

    //display pixel nodes
    imgscene->clear();
    imgscene->addPixmap(QPixmap::fromImage(*debugGraph));
    imgscene->installEventFilter(this);
    ui->graphicsView->setScene(imgscene);
    ui->graphicsView->resize(graphWidth + 10, graphHeight + 10);
    ui->graphicsView->show();

    //to be done: disable the mouse
}


