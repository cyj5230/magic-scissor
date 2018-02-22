#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "node.h"
#include "fibheap.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseNow(QMouseEvent *event);
    void initNodeBuffer(Node* nodes, QImage *image);
    void liveWireDP(int seedX, int seedY, Node* nodes, int expanded);
    void mouseInfo();
    void minPath(FibHeap* path, int inputX, int inputY, Node* nodes, int width, int height);
    void MakeCostGraph(QImage *costGraph, const Node* nodes, const QImage *image, int width, int height);

    // constructor functions
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage *rawImage;
    QImage *image;

private slots:

    void on_actionOpenImage_triggered();
    void on_actionCloseImage_triggered();
    void on_actionSize_x1_triggered();
    void on_actionSize_x2_triggered();
    void on_actionPixel_triggered();
    void on_actionLiveWire_triggered();
};

#endif // MAINWINDOW_H
