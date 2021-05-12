/********************************************************************************
** Form generated from reading UI file 'LifeAfterSchool.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIFEAFTERSCHOOL_H
#define UI_LIFEAFTERSCHOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LifeAfterSchoolClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LifeAfterSchoolClass)
    {
        if (LifeAfterSchoolClass->objectName().isEmpty())
            LifeAfterSchoolClass->setObjectName(QString::fromUtf8("LifeAfterSchoolClass"));
        LifeAfterSchoolClass->resize(600, 400);
        menuBar = new QMenuBar(LifeAfterSchoolClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        LifeAfterSchoolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LifeAfterSchoolClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LifeAfterSchoolClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LifeAfterSchoolClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        LifeAfterSchoolClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LifeAfterSchoolClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LifeAfterSchoolClass->setStatusBar(statusBar);

        retranslateUi(LifeAfterSchoolClass);

        QMetaObject::connectSlotsByName(LifeAfterSchoolClass);
    } // setupUi

    void retranslateUi(QMainWindow *LifeAfterSchoolClass)
    {
        LifeAfterSchoolClass->setWindowTitle(QCoreApplication::translate("LifeAfterSchoolClass", "LifeAfterSchool", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LifeAfterSchoolClass: public Ui_LifeAfterSchoolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIFEAFTERSCHOOL_H
