//
// Created by georg on 6/21/2021.
//

#include "ViewWindow.h"

void ViewWindow::init() {
    picture = new QPicture{};
    painter = new QPainter{picture};
    painter->setRenderHint(QPainter::Antialiasing);

    vector<Star> stars = this->service.getRepo().getStars();
    for(auto& s : stars){
        if(s.getName() == star.getName())
            painter->setBrush(Qt::red);
        else painter->setBrush(Qt::black);

        painter->drawEllipse(QPoint(s.getRA(), s.getDec()), 30 * s.getDiameter(), 30 * s.getDiameter());
    }
    painter->end();
    lbl = new QLabel{};
    lbl->setPicture(*picture);
    grid = new QGridLayout{this};
    grid->addWidget(lbl,0,0,10,10);
    this->show();

}

void ViewWindow::update() {
    delete grid;
    delete painter;
    delete lbl;
    delete picture;
    init();
}
