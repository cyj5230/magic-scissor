#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QString>
#include <QPoint>

namespace UI {
    class imageViewer;
}

class imageViewer: public QGraphicsView
{
    Q_OBJECT
public:
    QPoint mousePos;

    void mouseMoveEvent(QMouseEvent *mouse_event){
        this->mousePos = mouse_event->pos();
    }

    explicit imageViewer(QWidget *parent = 0);
    ~imageViewer();

protected:
    friend class MainWindow;

};

#endif // IMAGEVIEWER_H
