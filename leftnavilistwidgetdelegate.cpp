#include "LeftNaviListWidgetDelegate.h"
#include <QPainter>
#include <QDebug>

LeftNaviListWidgetDelegate::LeftNaviListWidgetDelegate(QObject *parent) : QStyledItemDelegate (parent)
{

}

QSize LeftNaviListWidgetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(100,44);
}

void LeftNaviListWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter,option,index);
//    // 设置字体
//    QFont font = painter->font();
//    font.setPointSize(12); // 设置字体大小
//    painter->setFont(font);

//    // 设置文本颜色为白色
//    QPen pen(Qt::white);
//    painter->setPen(pen);

//    // 获取项的文本
//    QString text = index.data(Qt::DisplayRole).toString();
//    qDebug() << text;
//    // 在项的矩形区域内居中绘制文本
//    painter->drawText(option.rect, Qt::AlignLeft | Qt::AlignVCenter, text);
}
