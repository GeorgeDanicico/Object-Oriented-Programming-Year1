//
// Created by georg on 6/21/2021.
//

#include "Table.h"


TableModel::TableModel(Repo& r, QObject *parent)
        : QAbstractTableModel{parent}, repo{r}
{
}

TableModel::~TableModel()
{
}

int TableModel::rowCount(const QModelIndex& parent) const
{
    int rows = this->repo.size_stars();
    return rows;
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    Star current = this->repo.getStar(row);

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return QString::fromStdString(current.getName());
            case 1:
                return QString::fromStdString(current.getConstellation());
            case 2:
                return QString::fromStdString("(" + to_string(current.getRA()) + "," + to_string(current.getDec()) + ")");
            case 3:
                return QString::fromStdString(to_string(current.getDiameter()));
            default:
                break;
        }
    }

    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString{ "Name" };
                case 1:
                    return QString{ "Constellation" };
                case 2:
                    return QString{ "Coordinates" };
                case 3:
                    return QString{"Diameter"};
                default:
                    break;
            }
        }
        if (orientation == Qt::Vertical) {
            return QString::fromStdString(to_string(section));
        }
    }

    return QVariant();
}