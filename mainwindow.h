#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseNow(QMouseEvent *event);
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
};

#endif // MAINWINDOW_H
