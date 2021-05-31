#pragma once

#include <QAbstractTableModel>
#include "repo.h"

class EventsTableModel : public QAbstractTableModel
{

private: 
	IRepo<TElem>* repo;

public:
	EventsTableModel(IRepo<TElem>* r, QObject* parent = NULL);
	~EventsTableModel();

	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

};
