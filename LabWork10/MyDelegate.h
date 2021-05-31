#pragma once
#include <qitemdelegate.h>
#include "repo.h"
#include <QAbstractTableModel>
#include <qstyleditemdelegate.h>
#include <qpainter.h>
#include <qstyle.h>
#include <qpushbutton.h>
#include <qicon.h>
#include <qevent.h>
#include <qmessagebox.h>

class ButtonDelegate :
    public QItemDelegate
{
    Q_OBJECT

private:
    IRepo<TElem>* repo;

public:
    ButtonDelegate(IRepo<TElem>* r, QObject *parent=NULL);
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);

};

