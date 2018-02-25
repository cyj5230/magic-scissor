
#include "mainwindow.h"
#include "mainwindow.cpp"
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication IntSc(argc, argv);
    MainWindow w;
    w.show();

    qDebug();
    return IntSc.exec();
}
