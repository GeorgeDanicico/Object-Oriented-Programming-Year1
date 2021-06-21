//
// Created by georg on 6/21/2021.
//

#include "Service.h"
#include <qwidget.h>
#include <qtableview.h>
#include "Table.h"
#include <qsortfilterproxymodel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qmessagebox.h>

class Window : public QWidget, public Observer{
private:
    Service& serv;
    User& user;
    TableModel* model;
    QSortFilterProxyModel* filterModel;
    QTableView* tableView;
    QVBoxLayout* mainLayout;
    QPushButton *actionButton, *deleteButton;
    QModelIndex current_index;
    QLineEdit* info;
public:
    Window(Service& s, User& u, TableModel* model) : serv{s}, user{u}, model{model}{
        init();
        make_connections();
    }
    void init();
    void populateTable();
    void make_connections();
    void update() override;

    ~Window()=default;
};

