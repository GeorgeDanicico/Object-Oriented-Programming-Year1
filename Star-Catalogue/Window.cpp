//
// Created by georg on 6/21/2021.
//

#include "Window.h"


void Window::init() {
    mainLayout = new QVBoxLayout{this};
    tableView = new QTableView{};
    filterModel = new QSortFilterProxyModel{};
    addButton = new QPushButton{"Add"};
    viewButton = new QPushButton{"View"};
    viewButton->setEnabled(false);
    searchBar = new QLineEdit{};
    searchedElements = new QListWidget{};

    filterModel->setSourceModel(model);
    tableView->setModel(filterModel);
    mainLayout->addWidget(tableView);

    tableView->setSortingEnabled(true);
    studied = new QCheckBox{"Studied Constellation"};
    QGridLayout* grid = new QGridLayout{};
    grid->addWidget(studied, 0, 0);
    mainLayout->addLayout(grid);

    name = new QLineEdit{};
    xCoord = new QLineEdit{};
    yCoord = new QLineEdit{};
    diameterValue = new QLineEdit{};

    QFormLayout* form = new QFormLayout{};
    form->addRow("Name: ", name);
    form->addRow("xCoord: ", xCoord);
    form->addRow("yCoord: ", yCoord);
    form->addRow("Diameter: ", diameterValue);
    form->addWidget(addButton);
    form->addWidget(viewButton);
    form->addRow("Search: ", searchBar);
    form->addWidget(searchedElements);
    mainLayout->addLayout(form);

}

void Window::make_connections() {

    QObject::connect(studied, &QCheckBox::stateChanged, this, [this](){

        if(studied->isChecked()){

            QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
            proxyModel->setSourceModel(model);
            proxyModel->setFilterRegExp(QRegExp(QString::fromStdString(astronomer.getConstellation()), Qt::CaseInsensitive, QRegExp::FixedString));
            proxyModel->setFilterKeyColumn(1);
            tableView->setModel(proxyModel);
        }
        else{
            filterModel->setSourceModel(model);
            tableView->setModel(filterModel);
        }
    });

    QObject::connect(addButton, &QPushButton::clicked, this, [this](){
        string name = this->name->text().toStdString();
        int xCoordinate = this->xCoord->text().toInt();
        int yCoordinate = this->yCoord->text().toInt();
        int Diameter = this->diameterValue->text().toInt();

        Star s{name, astronomer.getConstellation(),xCoordinate, yCoordinate, Diameter};
        if(Diameter <= 0 || name.empty() || !this->service.add_star(s)){
            QMessageBox::critical(this, "Error", "Error");
        }


    });

    QObject::connect(searchBar, &QLineEdit::textChanged, this, [this](){
        string characters = searchBar->text().toStdString();
        searchedElements->clear();
        if(characters.empty())
            return;

        vector<Star>& stars = this->service.getRepo().getStars();
        for(auto& s : stars){
            int find_succesfully = s.getName().find(characters);
            if(find_succesfully != string::npos){
                searchedElements->addItem(QString::fromStdString(s.getName()));

            }
        }
    });

    QObject::connect(tableView, &QTableView::clicked, this, [this](const QModelIndex& index){
        if(index.column() != 0)
            return;

        current_index = index;
        viewButton->setEnabled(true);
    });

    QObject::connect(viewButton, &QPushButton::clicked, this, [this](){

        string starName = current_index.data().toString().toStdString();
        Star star = service.find(starName);
        ViewWindow* view = new ViewWindow{service, star};


        viewButton->setEnabled(false);

    });
}

void Window::update() {
    this->model = new TableModel{this->service.getRepo()};
    filterModel->setSourceModel(model);
    tableView->setModel(filterModel);
}
