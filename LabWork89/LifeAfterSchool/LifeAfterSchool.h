#pragma once
#include <qwidget.h>
#include "Service/service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qabstractbutton.h>
#include <qtabwidget.h>
#include <QtWidgets/QMainWindow>
#include "ui_LifeAfterSchool.h"
#include "Service/service.h"

class LifeAfterSchool : public QMainWindow
{
    Q_OBJECT

public:
    LifeAfterSchool(QWidget *parent = Q_NULLPTR);

private:

    Ui::LifeAfterSchoolClass ui;
};
