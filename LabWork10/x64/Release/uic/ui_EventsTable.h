/********************************************************************************
** Form generated from reading UI file 'EventsTable.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTSTABLE_H
#define UI_EVENTSTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EventsTable
{
public:

    void setupUi(QWidget *EventsTable)
    {
        if (EventsTable->objectName().isEmpty())
            EventsTable->setObjectName(QString::fromUtf8("EventsTable"));
        EventsTable->resize(400, 300);

        retranslateUi(EventsTable);

        QMetaObject::connectSlotsByName(EventsTable);
    } // setupUi

    void retranslateUi(QWidget *EventsTable)
    {
        EventsTable->setWindowTitle(QCoreApplication::translate("EventsTable", "EventsTable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventsTable: public Ui_EventsTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTSTABLE_H
