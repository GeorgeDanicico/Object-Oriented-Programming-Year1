//
// Created by georg on 6/21/2021.
//

#pragma once
#include "ViewWindow.h"

class Window : public QWidget, public Observer{
private:
    Service& service;
    Astronomer& astronomer;
    QTableView* tableView{};
    QVBoxLayout* mainLayout{};
    TableModel* model;
    QSortFilterProxyModel* filterModel;
    QCheckBox* studied;
    QLineEdit * name, *xCoord, *yCoord, *diameterValue, *searchBar;
    QPushButton* addButton, *viewButton;
    QListWidget* searchedElements;
    QModelIndex current_index;

public:
    Window(Service& service, Astronomer& astronomer, TableModel* model) : service{service}, astronomer{astronomer}, model{model}{
        emit init();
        emit make_connections();
    }

    void init();
    void make_connections();
    void update() override;

};


