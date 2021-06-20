//
// Created by georg on 6/20/2021.
//

#pragma once
#include <qwidget.h>
#include "Observer.h"
#include "Service.h"
#include <qpainter.h>
#include <qbrush.h>
#include <qpicture.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpoint.h>

class Statistics : public QWidget, public Observer{
private:
    Service& service;
    QPicture* picture;
    QPainter* painter;
    QGridLayout* mainLayout;
    QLabel* lbl;

public:
    Statistics(Service& serv) : service{serv}{
        this->setWindowTitle("Statistics");
        init();
    }
    void update() override;
    void init();
};



