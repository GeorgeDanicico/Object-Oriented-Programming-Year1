#include "MyDelegate.h"

ButtonDelegate::ButtonDelegate(IRepo<TElem>* r, QObject* parent) : repo{r}
{
}

void ButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() != 5)
    {
        QItemDelegate::paint(painter, option, index);
        return;
    }
    QPushButton *button = new QPushButton{};
    button->setIcon(QIcon("playbtn.png"));
    button->setGeometry(option.rect);
    painter->save();
    painter->translate(option.rect.topLeft());
    button->render(painter);
    painter->restore();
}

bool ButtonDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        int row = index.row();
        string link = this->repo->get_element(row).getLink();

        string command = "start " + link;
        system(command.c_str());

    }
    return true;
}
