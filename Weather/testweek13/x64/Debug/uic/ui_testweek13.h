/********************************************************************************
** Form generated from reading UI file 'testweek13.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWEEK13_H
#define UI_TESTWEEK13_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testweek13Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *testweek13Class)
    {
        if (testweek13Class->objectName().isEmpty())
            testweek13Class->setObjectName(QString::fromUtf8("testweek13Class"));
        testweek13Class->resize(600, 400);
        menuBar = new QMenuBar(testweek13Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        testweek13Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(testweek13Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        testweek13Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(testweek13Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        testweek13Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(testweek13Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        testweek13Class->setStatusBar(statusBar);

        retranslateUi(testweek13Class);

        QMetaObject::connectSlotsByName(testweek13Class);
    } // setupUi

    void retranslateUi(QMainWindow *testweek13Class)
    {
        testweek13Class->setWindowTitle(QCoreApplication::translate("testweek13Class", "testweek13", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testweek13Class: public Ui_testweek13Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWEEK13_H
