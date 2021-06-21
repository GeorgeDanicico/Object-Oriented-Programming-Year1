//
// Created by georg on 6/21/2021.
//

#include "Window.h"


void Window::update() {
    this->populateTable();

}

void Window::init() {
    mainLayout = new QVBoxLayout{this};
    tableView = new QTableView{};

    actionButton = new QPushButton{};
    deleteButton = new QPushButton{"Delete"};
    deleteButton->setEnabled(false);
    info = new QLineEdit{};

    if(user.getType() == "programmer") {
        info->setReadOnly(true);
        actionButton->setText("Resolve");
        actionButton->setEnabled(false);
    }
    else actionButton->setText("Add");

    QGridLayout* grid = new QGridLayout{};
    grid->addWidget(info, 0, 0);
    grid->addWidget(actionButton, 0, 1);
    grid->addWidget(deleteButton, 1, 0);

    mainLayout->addWidget(tableView);
    mainLayout->addLayout(grid);
    this->populateTable();
}

void Window::make_connections() {
    QObject::connect(actionButton, &QPushButton::clicked, this, [this](){
        if(actionButton->text() == "Add"){
            string new_description = this->info->text().toStdString();
            this->info->clear();
            if(new_description.empty())
            {
                QMessageBox::critical(this, "Error", "No text.");
                return;
            }


            Issue new_issue{new_description, "open", user.getName(), ""};
            if(!this->serv.add_issue(new_issue)){
                QMessageBox::critical(this, "Error", "The issue has already been reported.");
            }
            return;
        }
        else{
            string description = current_index.data().toString().toStdString();

            vector<Issue> issues = this->serv.getRepo().getIssues();
            auto it = find_if(issues.begin(), issues.end(), [&](Issue& i1){
                return description == i1.getDescription();
            });

            (*it).setStatus("closed");
            (*it).setSolver(user.getName());
            this->serv.modify(*it);

            actionButton->setEnabled(false);
            tableView->clearSelection();
        }
    });

    QObject::connect(deleteButton, &QPushButton::clicked, this, [this](){
        string title = current_index.data().toString().toStdString();

        this->serv.remove_issue(title);

        this->tableView->clearSelection();
        deleteButton->setEnabled(false);
    });

    QObject::connect(tableView, &QTableView::clicked, this, [this](const QModelIndex& index){
        if(index.column() != 0) {
            tableView->clearSelection();
            return;
        }

        string description = index.data().toString().toStdString();

        vector<Issue> issues = this->serv.getRepo().getIssues();
        auto it = find_if(issues.begin(), issues.end(), [&](Issue& i1){
            return description == i1.getDescription();
        });

        if(user.getType() == "programmer"){
            if((*it).getStatus() == "closed"){
                deleteButton->setEnabled(true);
                actionButton->setEnabled(false);
            }
            else{
                deleteButton->setEnabled(false);
                actionButton->setEnabled(true);
            }
            current_index = index;
        }
        else {
            if((*it).getStatus() == "closed"){
                deleteButton->setEnabled(true);
            }
            else{
                deleteButton->setEnabled(false);
            }
            current_index = index;
        }
        return;

    });
}

void Window::populateTable() {
    if(tableView->model() == nullptr) {
        filterModel = new QSortFilterProxyModel{};
        filterModel->setSourceModel(model);
        filterModel->sort(0, Qt::AscendingOrder);
        tableView->setModel(filterModel);
        //tableView->setSortingEnabled(true);
    }
    else{
        this->model = new TableModel{this->serv.getRepo()};
        filterModel->setSourceModel(model);
        tableView->setModel(filterModel);

    }
}
