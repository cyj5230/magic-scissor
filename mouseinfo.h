#ifndef MAINWINDOW_H
#include "mainwindow.h"
#endif

#ifndef MOUSEINFO_H
#define MOUSEINFO_H
#include <QMouseEvent>
#include <QPoint>


class mouseInfo: public MainWindow
{

public:

    QPoint mousePos;

    explicit mouseInfo();
    ~mouseInfo();
/*
protected:
    QString mouseMoveEvent(QMouseEvent *mouse_event);
    void mousePressEvent(QMouseEvent *mouse_event);
    void mouseDoubleClickEvent(QMouseEvent *mouse_event);
*/

signals:
    void sendMousePosition(QPoint&);

};


#endif // MOUSEINFO_H
