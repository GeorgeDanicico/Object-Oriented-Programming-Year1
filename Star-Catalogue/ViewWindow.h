//
// Created by georg on 6/21/2021.
//

#pragma once
#include "service.h"
#include <qwidget.h>
#include <qtableview.h>
#include "Table.h"
#include <qsortfilterproxymodel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qcheckbox.h>
#include <qregexp.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qpainter.h>
#include <qpicture.h>
#include <qlabel.h>
#include <qbrush.h>

class ViewWindow : public QWidget, public Observer{
private:
    Service& service;
    Star& star;
    QPainter* painter;
    QGridLayout* grid;
    QLabel* lbl;
    QPicture* picture;

public:
    ViewWindow(Service& service, Star& star):service{service}, star{star}{
        init();
    }

    void init();
    void update() override;
};


