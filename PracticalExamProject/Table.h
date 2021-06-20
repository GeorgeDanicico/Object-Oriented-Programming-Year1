//
// Created by georg on 6/20/2021.
//

#pragma once
#include <qabstractitemmodel.h>
#include <QFont>
#include <qcolor.h>
#include <qbrush.h>
#include "Repo.h"

class TableModel : public QAbstractTableModel
{

private:
    Repo repo;

public:
    TableModel(Repo& r, QObject* parent = NULL);
    ~TableModel();

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void resetModel(){
        this->beginResetModel();
        this->endResetModel();
    }
};


