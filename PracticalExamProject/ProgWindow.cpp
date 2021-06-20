//
// Created by georg on 6/20/2021.
//

#include "ProgWindow.h"

void ProgWindow::initGUI() {
    this->setWindowTitle(QString::fromStdString(prog.getName()));
    mainLayout = new QVBoxLayout{this};
    tableView = new QTableView{};
    tableView->setSortingEnabled(true);
    addButton = new QPushButton{"Add"};
    reviseButton = new QPushButton{"Revise"};
    reviseButton->setEnabled(false);
    new_file = new QLineEdit{};
    filterModel = new QSortFilterProxyModel{};
    emit populateTable();

    vector<SourceFile> files = this->service.getRepo().getSources();
    int revised = count_if(files.begin(), files.end(), [&](SourceFile& f){ return f.getStatus() == "revised" && f.getReviser() == prog.getName();});
    int remaining = (prog.getMust() - revised);
    revisedFiles = new QLabel{QString::fromStdString("Revised: " + to_string(revised))};
    remainingFiles = new QLabel{QString::fromStdString("Remaining: " + to_string(remaining))};
    QGridLayout* grid = new QGridLayout{};
    grid->addWidget(revisedFiles, 0, 0);
    grid->addWidget(remainingFiles,0 ,1);
    grid->addWidget(new_file, 1, 0, 1, 2);
    grid->addWidget(addButton, 1, 2);
    grid->addWidget(reviseButton, 2, 0);
    mainLayout->addLayout(grid);

}

void ProgWindow::populateTable() {
    if(this->tableView->model() == nullptr) {
        TableModel *new_model = new TableModel{this->service.getRepo()};
        filterModel->setSourceModel(model);
        filterModel->sort(0, Qt::AscendingOrder);
        tableView->setModel(filterModel);
        mainLayout->addWidget(tableView);
    }
    else{
        this->model = new TableModel{this->service.getRepo()};
        filterModel->setSourceModel(model);
        tableView->setModel(filterModel);

    }
}

void ProgWindow::update() {
    emit this->populateTable();
}

void ProgWindow::make_connections() {
    QObject::connect(addButton, &QPushButton::clicked, this, [this](){
        string text = this->new_file->text().toStdString();

        if(text.empty()){
            QMessageBox::critical(this, "Error", "No new file provided.");
            return;
        }

        SourceFile newFile{text, "not revised", this->prog.getName(), ""};
        if(!this->service.add_file(newFile)){
            QMessageBox::critical(this, "Error", "The file already exists.");
            return;
        }
        QMessageBox::critical(this, "Succes", "New file added.");
        this->new_file->clear();

    });

    QObject::connect(this->tableView, &QTableView::clicked, this ,[=](const QModelIndex& index){

        if(index.column() != 0) {
            this->tableView->clearSelection();
            return;
        }
        string value = index.data().toString().toStdString();
        vector<SourceFile> v = this->service.getRepo().getSources();
        auto it = find_if(v.begin(), v.end(), [&](SourceFile &source){ return value == source.getName();});
        if(it != v.end()){
            SourceFile obj = *it;
            if(obj.getStatus() == "not revised"){
                this->reviseButton->setEnabled(true);
                current_index = index;
            }
        }
        this->tableView->clearSelection();

    });

    QObject::connect(this->reviseButton, &QPushButton::clicked, this, [this](){
        this->tableView->clearSelection();

        string value = current_index.data().toString().toStdString();
        vector<SourceFile> v = this->service.getRepo().getSources();
        auto it = find_if(v.begin(), v.end(), [&](SourceFile &source){ return value == source.getName();});\

        this->service.modify(*it, prog);
        this->updateLabels();
        this->reviseButton->setEnabled(false);
    });
}

void ProgWindow::updateLabels() {
    int revised = prog.getRevised();
    int remaining = prog.getMust() - revised;
    revisedFiles->setText(QString::fromStdString("Revised: " + to_string(revised)));
    remainingFiles->setText(QString::fromStdString("Remaining: " + to_string(remaining)));

    if(remaining == 0){
        QMessageBox::critical(this, "Congratulations!", "You revised the required number of files.");
    }
}
