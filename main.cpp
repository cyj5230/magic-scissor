#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication IntSc(argc, argv);
    MainWindow w;

    w.show();

    return IntSc.exec();
}
