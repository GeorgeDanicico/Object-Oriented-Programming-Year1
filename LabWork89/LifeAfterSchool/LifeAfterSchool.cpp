#include "LifeAfterSchool.h"
#include <qwidget.h>
#include <qlistwidget.h>

LifeAfterSchool::LifeAfterSchool( QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QListWidget* new_list = new QListWidget{};

    this->setCentralWidget(new_list);
}

