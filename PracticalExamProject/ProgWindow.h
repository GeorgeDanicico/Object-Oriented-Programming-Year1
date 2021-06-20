//
// Created by georg on 6/20/2021.
//
#pragma once
#include "Service.h"
#include <qwidget.h>
#include <qtableview.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qsortfilterproxymodel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include "Observer.h"
#include "Table.h"

class ProgWindow : public QWidget, public Observer{
private:
    Service& service;
    Programmer& prog;
    TableModel* model;
    QLabel* revisedFiles, *remainingFiles;
    QTableView* tableView;
    QLineEdit* new_file;
    QPushButton* addButton, *reviseButton;
    QVBoxLayout* mainLayout;
    QModelIndex current_index;
    QSortFilterProxyModel* filterModel;
public:
    ProgWindow(Service& service, Programmer& prog, TableModel* model):service{service}, prog{prog}, model{model}{
        emit initGUI();
        emit make_connections();
    }
    void make_connections();
    void update() override;
    void populateTable();
    void initGUI();

    void updateLabels();

};


