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
#include "imagearray.h"

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
    void liveWireDP(int seedX, int seedY, Node* nodes);
    void mouseInfo();
    void minPath(FibHeap* path, int inputX, int inputY, Node* nodes, int width);
    std::list<std::pair<int, int>> minPath(int inputX, int inputY, Node* nodes);
    void MakeCostGraph(QImage *costGraph, Node* nodes, QImage *image, int width, int height);

    void toEdgeVec(int inputX, int inputY, Node* nodes, bool realtime);
    void drawEdge();
    void drawTempEdge();
    void drawPix(int x, int y);

    QGraphicsScene *imgscene = new QGraphicsScene;

    // constructor functions
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void imageSizeChange(double scaleFactor);
    bool genBorder(bool temp);
    void tempPath(int spx, int spy, int epx, int epy, bool realtime);
    bool foundArea(int x, int y);
    bool useTempPath = true;

private:
    Ui::MainWindow *ui;
    QImage *rawImage, *image;
    QImage *mkimage = new QImage;
    QImage *tempImage = new QImage;
    int mousex, mousey, wirex, wirey;
    int startx, starty, endx, endy;
    imArray imgarray = imArray();
    QString imgFileName;

    Node* nodes;
    bool undoDisabled = true;



    bool scissorRunning = false;
    bool restartScissor = false;
    bool finishScissor = false;

private slots:

    void on_actionOpenImage_triggered();
    void on_actionCloseImage_triggered();
    void on_actionSize_x1_triggered();
    void on_actionSize_x2_triggered();
    void on_actionPixel_triggered();
    void on_actionLiveWire_triggered();
    void on_actiontest_triggered();
};

#endif // MAINWINDOW_H
