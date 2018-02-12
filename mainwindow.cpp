#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Intelligent Scissor");
    resize(800, 600);

    this->image = new QImage();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this, "open image file",
                ".",
                "Image files (*.bmp, *.jpg *png);;All files(*.*)");
    if (fileName != ""){
        if (image->load(fileName)){
            QGraphicsScene *scene = new QGraphicsScene;
            scene->addPixmap(QPixmap::fromImage(*image));
            ui->graphicsView->setScene(scene);
            ui->graphicsView->resize(image->width() + 10, image->height() + 10);
            ui->graphicsView->show();
        }
    }
}
