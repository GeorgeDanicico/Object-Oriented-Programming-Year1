#pragma once
#include "Repository.h"
#include <qabstractitemmodel.h>
#include <qfont.h>
#include <qcolor.h>
#include <qbrush.h>


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
        QModelIndex topLeft = this->index(1, 1);
        QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
        emit layoutChanged();
        emit dataChanged(topLeft, bottomRight);
    }
};

