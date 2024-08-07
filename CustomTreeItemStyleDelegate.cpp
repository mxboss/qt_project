#include "CustomTreeItemStyleDelegate.h"
#include <QTreeView>
#include "CustomTreeItem.h"
#include <QPainter>
#include <QDebug>
#include <QAbstractItemModel>
#include <QCheckBox>
#include <QApplication>
#include <QMouseEvent>
#include <QLineEdit>
#include <QHeaderView>
#include <QTreeView>
#include <QWidget>

namespace {
    constexpr int IDENT = 20;
    const QColor COLOR_HOVER(250, 138, 56, 255);
    const QColor COLOR_SELECTED(248, 192, 80, 255);
    constexpr int LINE_HEIGHT = 30;
    constexpr qreal TRIANGLE_WIDTH = IDENT / 4.0;
    constexpr qreal PADDING = IDENT / 8.0;
    const QColor HIGHTLIGHT_TEXT_COLOR(255, 0, 0);
}
CustomTreeItemStyleDelegate::CustomTreeItemStyleDelegate(QTreeView *view,QWidget *parent)
    :m_treeView(view)
{

    m_treeView->setUniformRowHeights(false);
    m_treeView->setWordWrap(true);
    connect(m_treeView->header(), &QHeaderView::sectionResized,this,[this](){
        m_treeView->doItemsLayout();
    });
}

CustomTreeItemStyleDelegate::~CustomTreeItemStyleDelegate()
{
    delete m_treeView;
}

void CustomTreeItemStyleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    const_cast<QAbstractItemModel *>(index.model())->setData(index,100,Qt::UserRole+1);
    CustomTreeItem *item = index.data(Qt::UserRole).value<CustomTreeItem *>();
    QVector<QVariant> dataArr = item->itemData();
    //qDebug() << item->itemData();
    QPen p = painter->pen();
    if (index.column() == 0) {
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            painter->fillRect(option.rect, COLOR_HOVER);
        }
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->fillRect(option.rect, COLOR_SELECTED);
        }

        painter->drawText(option.rect,Qt::AlignCenter,QString::number(dataArr[index.column()].toInt()));
    } else if (index.column() == 1) {
        if (mMatchWord.length() > 0) {
            DrawKeyword(painter,option,index);
        } else {
            QString text = dataArr[1].toString();
            painter->drawText(option.rect,Qt::AlignLeft | Qt::AlignVCenter,text);
        }
    } else if (index.column() == 2) {
        painter->setPen(Qt::black);
        painter->drawText(option.rect,Qt::AlignLeft | Qt::AlignVCenter,dataArr[2].toString());
    } else if (index.column() == 3) {
        if (item->data(3).canConvert<QCheckBox *>()) {
            QCheckBox *checkbox = qvariant_cast<QCheckBox *>(item->data(3));
            QStyleOptionButton optionBtn;
            optionBtn.state |= checkbox->isChecked()? QStyle::State_On:QStyle::State_Off;
            if (checkbox->isDown()) {
                optionBtn.state |= QStyle::State_MouseOver;
            }
            optionBtn.rect = option.rect;
            int xOffset = (option.rect.width() - QApplication::style()->pixelMetric(QStyle::PM_IndicatorWidth)) / 2;
            optionBtn.rect.adjust(xOffset, 0, xOffset, 0);
            QApplication::style()->drawControl(QStyle::CE_CheckBox, &optionBtn, painter);
        }
    }
    QStyledItemDelegate::paint(painter,option,index);
}

QWidget * CustomTreeItemStyleDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(option)
    if (index.column() != 3) {
        QLineEdit *le = new QLineEdit(parent);
        return le;
    }
    return nullptr;
}

bool CustomTreeItemStyleDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{

    CustomTreeItem *item = index.data(Qt::UserRole).value<CustomTreeItem *>();
    QMouseEvent *mEvent = static_cast<QMouseEvent *>(event);
    if (index.column() == 3) {
        QCheckBox *checkBox = qvariant_cast<QCheckBox *>(item->data(3));
        if (event->type() == QEvent::MouseButtonRelease) {
            checkBox->setChecked(!checkBox->isChecked());
            return true;
        }
        if (event->type() == QEvent::MouseMove) {
            checkBox->setDown(true);
            return true;
        }
        return false;
    } else {
        return QStyledItemDelegate::editorEvent(event,model,option,index);;
    }
}

void CustomTreeItemStyleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() != 3) {
        CustomTreeItem *item = index.data(Qt::UserRole).value<CustomTreeItem *>();
        item->setData(index.column(), QVariant(qobject_cast<QLineEdit *>(editor)->text()));
    }
}

//void CustomTreeItemStyleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    CustomTreeItem *item = index.data(Qt::EditRole).value<CustomTreeItem *>();
//    QLineEdit *lineE = qobject_cast<QLineEdit *>(editor);
//    lineE->setText(item->data(index.column()).toString());
//    qDebug() << item->data(index.column());
//}

void CustomTreeItemStyleDelegate::DrawKeyword(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    CustomTreeItem *item = index.data(Qt::UserRole).value<CustomTreeItem *>();
    QStringList list = SpliteWord(item->itemData()[index.column()].toString());
    QPen p = painter->pen();
    QFontMetrics fm = painter->fontMetrics();
    double ident = PADDING;
    for (int i = 0; i < list.size(); i++) {
        painter->save();
        if (list[i] == mMatchWord) {
            p.setColor(Qt::yellow);
            painter->setPen(p);
            if (ident > option.rect.width()) {
                painter->restore();
                return;
            }
            QRect rc = option.rect.adjusted(ident, 0, 0, 0);
            painter->drawText(rc, Qt::AlignVCenter, list[i]);
            ident += fm.horizontalAdvance(list[i]);
        } else {
            if (option.state.testFlag(QStyle::State_Selected)) {
                p.setColor(COLOR_SELECTED);
                painter->setPen(p);
            } else {
                p.setColor(Qt::black);
                painter->setPen(p);
            }
            if (ident > option.rect.width()) {
                painter->restore();
                return;
            }
            painter->drawText(option.rect.adjusted(ident, 0, 0, 0), Qt::AlignVCenter, list[i]);
            ident += fm.horizontalAdvance(list[i]);
        }
        painter->restore();
    }
    qDebug()<<list;
}

QStringList CustomTreeItemStyleDelegate::SpliteWord(QString originWord) const
{
    if (mMatchWord.length() < 1) return QStringList();
    QStringList list;
    list = originWord.split(mMatchWord);
    //qDebug() << "SpliteWord:" << list;
    if (mMatchWord == originWord) {
        list.append(mMatchWord);
    } else {
        if (list.size() == 2) {
            if (list[0] == "") {
                list.insert(0, mMatchWord);
            } else if (list[1] == "") {
                list.append(mMatchWord);
            } else {
                list.insert(1, mMatchWord);
            }
        }
    }
    //qDebug() << "insert:" << list;
    return list;
}




























