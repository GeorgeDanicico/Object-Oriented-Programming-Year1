#include "EventsTableModel.h"

EventsTableModel::EventsTableModel(IRepo<TElem>* r, QObject *parent)
	: QAbstractTableModel{parent}, repo{r}
{
}

EventsTableModel::~EventsTableModel()
{
}

int EventsTableModel::rowCount(const QModelIndex& parent) const
{
	int rows = this->repo->size();
	return rows;
}

int EventsTableModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant EventsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	TElem current_event = this->repo->get_element(row);

	if (role == Qt::DisplayRole) {
		switch (index.column()) {
		case 0:
			return QString::fromStdString(current_event.getTitle());
		case 1:
			return QString::fromStdString(current_event.getDescription());
		case 2:
			return QString::fromStdString(current_event.getDate().toString());
		case 3:
			return QString::fromStdString(to_string(current_event.getPeopleNr()));
		case 4:
			return QString::fromStdString(current_event.getLink());
		break;
		}
	}

	return QVariant();
}

QVariant EventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString{ "Title" };
			case 1:
				return QString{ "Description" };
			case 2:
				return QString{ "Date" };
			case 3:
				return QString{ "People" };
			case 4:
				return QString{ "Link" };
			case 5:
				return QString{ "Open Link" };
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
