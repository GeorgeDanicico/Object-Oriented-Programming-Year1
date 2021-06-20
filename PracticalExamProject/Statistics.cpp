//
// Created by georg on 6/20/2021.
//

#include "Statistics.h"

void Statistics::init() {

    vector<Programmer>& prog = this->service.getRepo().getProgrammers();
    picture = new QPicture{};
    painter = new QPainter{picture};
    painter->setRenderHint(QPainter::Antialiasing);
    int x = 0, y = 100;
    for(auto& p : prog){
        if(p.getMust() <= p.getRevised()){
            painter->setPen(Qt::blue);
        }
        else painter->setPen(Qt::red);

        painter->drawEllipse(QPoint(x, y), p.getRevised()*30, p.getRevised()*30);
        painter->drawText(QPoint(x, y + p.getRevised()*30 + 5), QString::fromStdString(p.getName()));

        y = y - 100;
    }

    painter->end();
    this->lbl = new QLabel{};
    lbl->setPicture(*picture);
    mainLayout = new QGridLayout{};
    mainLayout->addWidget(lbl,0 ,0, 3, 3);
    this->setLayout(mainLayout);
    this->show();
}

void Statistics::update() {
    delete picture;
    delete painter;
    delete mainLayout;
    delete lbl;
    emit init();
}
