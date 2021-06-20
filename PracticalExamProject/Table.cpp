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
    int rows = this->repo.size_sources();
    return rows;
}

int TableModel::columnCount(const QModelIndex& parent) const
{
    return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    SourceFile current = this->repo.getFile(row);

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return QString::fromStdString(current.getName());
            case 1:
                return QString::fromStdString(current.getStatus());
            case 2:
                return QString::fromStdString(current.getCreator());
            case 3:
                return QString::fromStdString(current.getReviser());
            default:
                break;
        }
    }

    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        if(current.getStatus() == "not revised")
            font.setBold(true);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
        if(current.getStatus() == "revised")
            return QBrush{ QColor("green")};
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
                    return QString{ "Status" };
                case 2:
                    return QString{ "Creator" };
                case 3:
                    return QString{ "Revisor" };
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