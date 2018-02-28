/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSize_x1;
    QAction *actionSize_x2;
    QAction *actionOpenImage;
    QAction *actionCloseImage;
    QAction *actionPixel;
    QAction *actionmouseTrack;
    QAction *actionliveWire;
    QAction *actionSave_Mask;
    QAction *actionSave_Contour;
    QAction *actionundo;
    QAction *actiontest;
    QAction *actionPixel_Node;
    QAction *actionCost_Graph;
    QAction *actionPath_Tree;
    QAction *actionMin_Path;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuIntelligent_Scissor;
    QMenu *menuEdge;
    QMenu *menuSize;
    QMenu *menuDebug;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setMouseTracking(true);
        actionSize_x1 = new QAction(MainWindow);
        actionSize_x1->setObjectName(QStringLiteral("actionSize_x1"));
        actionSize_x2 = new QAction(MainWindow);
        actionSize_x2->setObjectName(QStringLiteral("actionSize_x2"));
        actionOpenImage = new QAction(MainWindow);
        actionOpenImage->setObjectName(QStringLiteral("actionOpenImage"));
        actionCloseImage = new QAction(MainWindow);
        actionCloseImage->setObjectName(QStringLiteral("actionCloseImage"));
        actionPixel = new QAction(MainWindow);
        actionPixel->setObjectName(QStringLiteral("actionPixel"));
        actionmouseTrack = new QAction(MainWindow);
        actionmouseTrack->setObjectName(QStringLiteral("actionmouseTrack"));
        actionliveWire = new QAction(MainWindow);
        actionliveWire->setObjectName(QStringLiteral("actionliveWire"));
        actionSave_Mask = new QAction(MainWindow);
        actionSave_Mask->setObjectName(QStringLiteral("actionSave_Mask"));
        actionSave_Contour = new QAction(MainWindow);
        actionSave_Contour->setObjectName(QStringLiteral("actionSave_Contour"));
        actionundo = new QAction(MainWindow);
        actionundo->setObjectName(QStringLiteral("actionundo"));
        actiontest = new QAction(MainWindow);
        actiontest->setObjectName(QStringLiteral("actiontest"));
        actionPixel_Node = new QAction(MainWindow);
        actionPixel_Node->setObjectName(QStringLiteral("actionPixel_Node"));
        actionCost_Graph = new QAction(MainWindow);
        actionCost_Graph->setObjectName(QStringLiteral("actionCost_Graph"));
        actionPath_Tree = new QAction(MainWindow);
        actionPath_Tree->setObjectName(QStringLiteral("actionPath_Tree"));
        actionMin_Path = new QAction(MainWindow);
        actionMin_Path->setObjectName(QStringLiteral("actionMin_Path"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMouseTracking(true);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(6, 6, 711, 541));
        graphicsView->setMouseTracking(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        menuIntelligent_Scissor = new QMenu(menuBar);
        menuIntelligent_Scissor->setObjectName(QStringLiteral("menuIntelligent_Scissor"));
        menuEdge = new QMenu(menuBar);
        menuEdge->setObjectName(QStringLiteral("menuEdge"));
        menuSize = new QMenu(menuBar);
        menuSize->setObjectName(QStringLiteral("menuSize"));
        menuDebug = new QMenu(menuBar);
        menuDebug->setObjectName(QStringLiteral("menuDebug"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuIntelligent_Scissor->menuAction());
        menuBar->addAction(menuEdge->menuAction());
        menuBar->addAction(menuSize->menuAction());
        menuBar->addAction(menuDebug->menuAction());
        menuIntelligent_Scissor->addSeparator();
        menuIntelligent_Scissor->addAction(actionOpenImage);
        menuIntelligent_Scissor->addAction(actionCloseImage);
        menuIntelligent_Scissor->addAction(actionSave_Mask);
        menuIntelligent_Scissor->addAction(actionSave_Contour);
        menuEdge->addAction(actionPixel);
        menuEdge->addAction(actionmouseTrack);
        menuEdge->addAction(actionliveWire);
        menuEdge->addAction(actionundo);
        menuEdge->addAction(actiontest);
        menuSize->addAction(actionSize_x1);
        menuSize->addAction(actionSize_x2);
        menuDebug->addAction(actionPixel_Node);
        menuDebug->addAction(actionCost_Graph);
        menuDebug->addAction(actionPath_Tree);
        menuDebug->addAction(actionMin_Path);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSize_x1->setText(QApplication::translate("MainWindow", "Size x1", nullptr));
        actionSize_x2->setText(QApplication::translate("MainWindow", "Size x2", nullptr));
        actionOpenImage->setText(QApplication::translate("MainWindow", "Open", nullptr));
        actionCloseImage->setText(QApplication::translate("MainWindow", "Close", nullptr));
        actionPixel->setText(QApplication::translate("MainWindow", "Pixel", nullptr));
        actionmouseTrack->setText(QApplication::translate("MainWindow", "mouseTrack", nullptr));
        actionliveWire->setText(QApplication::translate("MainWindow", "LiveWire", nullptr));
        actionSave_Mask->setText(QApplication::translate("MainWindow", "Save Mask", nullptr));
        actionSave_Contour->setText(QApplication::translate("MainWindow", "Save Contour", nullptr));
        actionundo->setText(QApplication::translate("MainWindow", "undo", nullptr));
        actiontest->setText(QApplication::translate("MainWindow", "test", nullptr));
        actionPixel_Node->setText(QApplication::translate("MainWindow", "Pixel Node", nullptr));
        actionCost_Graph->setText(QApplication::translate("MainWindow", "Cost Graph", nullptr));
        actionPath_Tree->setText(QApplication::translate("MainWindow", "Path Tree", nullptr));
        actionMin_Path->setText(QApplication::translate("MainWindow", "Min Path", nullptr));
        menuIntelligent_Scissor->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdge->setTitle(QApplication::translate("MainWindow", "Edge", nullptr));
        menuSize->setTitle(QApplication::translate("MainWindow", "Size", nullptr));
        menuDebug->setTitle(QApplication::translate("MainWindow", "Debug", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
