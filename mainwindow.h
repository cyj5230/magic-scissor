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
    void initNodeBuffer();
    void liveWireDP(int seedX, int seedY, int expand = -1, double maxCost = 0.0000);
    void mouseInfo();
    void minPath(int inputX, int inputY);

    void makeCostGraph(int width, int height);
    void makePixelNodes(int width, int height);
    void makePathTree(int width, int height, int expand);
    void makeMinPath(int width, int height);

    void toEdgeVec(int inputX, int inputY, bool realtime);
    void drawEdge();
    void drawTempEdge();
    void drawPix(int x, int y);

    QGraphicsScene *imgscene = new QGraphicsScene;

    imArray getia(){return this->imgarray;}

    // constructor functions
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void imageSizeChange(double scaleFactor);
    bool genBorder(bool temp);
    void tempPath(int spx, int spy, int epx, int epy, bool realtime);
    bool foundArea(int x, int y);
    bool useTempPath = false;

private:
    Ui::MainWindow *ui;
    QImage *rawImage, *image, *debugGraph;
    QImage *mkimage = new QImage;
    QImage *tempImage = new QImage;
    int mousex, mousey, wirex, wirey;
    int startx, starty, endx, endy;
    imArray imgarray = imArray();
    QString imgFileName;

    Node* nodes; Node* pnode;
    std::list<Node> minPathList;
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
    void on_actionPixel_Node_triggered();
    void on_actionCost_Graph_triggered();
    void on_actionPath_Tree_triggered();
    void on_actionMin_Path_triggered();
    void on_actionSave_Contour_triggered();
    void on_actionSave_Mask_triggered();
};

#endif // MAINWINDOW_H
