/********************************************************************************
** Form generated from reading UI file 'A10.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A10_H
#define UI_A10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_A10Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *A10Class)
    {
        if (A10Class->objectName().isEmpty())
            A10Class->setObjectName(QString::fromUtf8("A10Class"));
        A10Class->resize(600, 400);
        menuBar = new QMenuBar(A10Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        A10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(A10Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        A10Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(A10Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        A10Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(A10Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        A10Class->setStatusBar(statusBar);

        retranslateUi(A10Class);

        QMetaObject::connectSlotsByName(A10Class);
    } // setupUi

    void retranslateUi(QMainWindow *A10Class)
    {
        A10Class->setWindowTitle(QCoreApplication::translate("A10Class", "A10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class A10Class: public Ui_A10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A10_H
