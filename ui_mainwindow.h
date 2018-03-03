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
    QAction *actionReload;
    QAction *actionWork_Mode;
    QAction *actionCost_Graph;
    QAction *actionPath_Tree;
    QAction *actionMin_Path;
    QAction *actionPixel_Node;
    QAction *action3_x_3;
    QAction *action5_x_5;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuIntelligent_Scissor;
    QMenu *menuEdge;
    QMenu *menuSize;
    QMenu *menuMode;
    QMenu *menuDebug_3;
    QMenu *menuBlur;
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
        actionReload = new QAction(MainWindow);
        actionReload->setObjectName(QStringLiteral("actionReload"));
        actionWork_Mode = new QAction(MainWindow);
        actionWork_Mode->setObjectName(QStringLiteral("actionWork_Mode"));
        actionCost_Graph = new QAction(MainWindow);
        actionCost_Graph->setObjectName(QStringLiteral("actionCost_Graph"));
        actionPath_Tree = new QAction(MainWindow);
        actionPath_Tree->setObjectName(QStringLiteral("actionPath_Tree"));
        actionMin_Path = new QAction(MainWindow);
        actionMin_Path->setObjectName(QStringLiteral("actionMin_Path"));
        actionPixel_Node = new QAction(MainWindow);
        actionPixel_Node->setObjectName(QStringLiteral("actionPixel_Node"));
        action3_x_3 = new QAction(MainWindow);
        action3_x_3->setObjectName(QStringLiteral("action3_x_3"));
        action5_x_5 = new QAction(MainWindow);
        action5_x_5->setObjectName(QStringLiteral("action5_x_5"));
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
        menuMode = new QMenu(menuBar);
        menuMode->setObjectName(QStringLiteral("menuMode"));
        menuDebug_3 = new QMenu(menuMode);
        menuDebug_3->setObjectName(QStringLiteral("menuDebug_3"));
        menuBlur = new QMenu(menuBar);
        menuBlur->setObjectName(QStringLiteral("menuBlur"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuIntelligent_Scissor->menuAction());
        menuBar->addAction(menuMode->menuAction());
        menuBar->addAction(menuEdge->menuAction());
        menuBar->addAction(menuSize->menuAction());
        menuBar->addAction(menuBlur->menuAction());
        menuIntelligent_Scissor->addSeparator();
        menuIntelligent_Scissor->addAction(actionOpenImage);
        menuIntelligent_Scissor->addAction(actionCloseImage);
        menuIntelligent_Scissor->addAction(actionSave_Mask);
        menuIntelligent_Scissor->addAction(actionSave_Contour);
        menuEdge->addAction(actionPixel);
        menuEdge->addAction(actionmouseTrack);
        menuEdge->addAction(actionundo);
        menuEdge->addAction(actiontest);
        menuSize->addAction(actionSize_x1);
        menuSize->addAction(actionSize_x2);
        menuMode->addAction(actionWork_Mode);
        menuMode->addAction(menuDebug_3->menuAction());
        menuDebug_3->addAction(actionPixel_Node);
        menuDebug_3->addAction(actionCost_Graph);
        menuDebug_3->addAction(actionPath_Tree);
        menuDebug_3->addAction(actionMin_Path);
        menuBlur->addSeparator();
        menuBlur->addAction(action3_x_3);
        menuBlur->addAction(action5_x_5);

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
        actionReload->setText(QApplication::translate("MainWindow", "Reload", nullptr));
        actionWork_Mode->setText(QApplication::translate("MainWindow", "Work", nullptr));
        actionCost_Graph->setText(QApplication::translate("MainWindow", "Cost Graph", nullptr));
        actionPath_Tree->setText(QApplication::translate("MainWindow", "Path Tree", nullptr));
        actionMin_Path->setText(QApplication::translate("MainWindow", "Min Path", nullptr));
        actionPixel_Node->setText(QApplication::translate("MainWindow", "Pixel Node", nullptr));
        action3_x_3->setText(QApplication::translate("MainWindow", "3 x 3", nullptr));
        action5_x_5->setText(QApplication::translate("MainWindow", "5 x 5", nullptr));
        menuIntelligent_Scissor->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdge->setTitle(QApplication::translate("MainWindow", "Edge", nullptr));
        menuSize->setTitle(QApplication::translate("MainWindow", "Size", nullptr));
        menuMode->setTitle(QApplication::translate("MainWindow", "Mode", nullptr));
        menuDebug_3->setTitle(QApplication::translate("MainWindow", "Debug", nullptr));
        menuBlur->setTitle(QApplication::translate("MainWindow", "Blur", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
