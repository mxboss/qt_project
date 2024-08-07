#ifndef LEFTNAVILISTWIDGETDELEGATE_H
#define LEFTNAVILISTWIDGETDELEGATE_H

#include <QStyledItemDelegate>

class LeftNaviListWidgetDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    LeftNaviListWidgetDelegate(QObject *parent = nullptr);

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // LEFTNAVILISTWIDGETDELEGATE_H
