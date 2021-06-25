#pragma once

#include "Service.h"
#include <QtWidgets/QMainWindow>
#include "ui_testWeek13.h"
#include <qlayout.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <qbrush.h>
#include <qcheckbox.h>
#include <qslider.h>
#include <qvector.h>


class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& service);

private:

    void initGUI();
    void makeConnections();
    void initWeathers();
    void initChecks();
    void filterWeathers();
    void updateDesc(vector<string> desc);

    void change();
    Service& service;
    
    QVector<QCheckBox*> checks;
    QSlider* Slider;


    vector<string> alldesc;
    int sliderValue = 100;
    QVBoxLayout* mainLayout;
    QListWidget* list;
    QLineEdit* line, * nrline;
    QPushButton* btnBack;

    void clearLayout();

};