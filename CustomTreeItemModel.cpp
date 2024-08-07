#include "CustomTreeItemModel.h"
#include <QDebug>

CustomTreeItemModel::CustomTreeItemModel(QStringList headers,QObject *parent)
    : QAbstractItemModel(parent)
{
    mHeaders = headers;
    mRootItem = new CustomTreeItem();
    ss = QSize(28,44);
}
CustomTreeItemModel::~CustomTreeItemModel()
{
    delete mRootItem;
}

QVariant CustomTreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        return mHeaders.at(section);
    }
    return QVariant();
}

QModelIndex CustomTreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) return QModelIndex();
    CustomTreeItem *parentItem;
    if (!parent.isValid()) {
        parentItem = mRootItem;
    } else {
        parentItem = static_cast<CustomTreeItem *>(parent.internalPointer());
    }

    CustomTreeItem *childItem = parentItem->child(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex CustomTreeItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }
    CustomTreeItem *childItem = static_cast<CustomTreeItem *>(index.internalPointer());
    CustomTreeItem *parentItem = childItem->parentItem();
    if (parentItem == mRootItem) {
        return QModelIndex();
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

int CustomTreeItemModel::rowCount(const QModelIndex &parent) const
{
    CustomTreeItem *parentItem;
    if (parent.column() > 0) {
        return 0;
    }
    if (!parent.isValid())
        parentItem = mRootItem;
    else {
        parentItem = static_cast<CustomTreeItem *>(parent.internalPointer());
    }
    return parentItem->childCount();

}

int CustomTreeItemModel::columnCount(const QModelIndex &parent) const
{
    return mHeaders.count();
}

Qt::ItemFlags CustomTreeItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    //节点是否允许编辑
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsEditable;
//    qDebug()<<"Qt::ItemFlags CustomTreeItemModel::flags(const QModelIndex &index) const" << flags;
    return flags;
}

QVariant CustomTreeItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    CustomTreeItem *item = static_cast<CustomTreeItem *>(index.internalPointer());

    if (role == Qt::UserRole) {
        return QVariant::fromValue<CustomTreeItem *>(item);
    } else if (Qt::SizeHintRole == role) {
        return QVariant(ss);
    } else if (Qt::EditRole == role) {
//        qDebug() << "EditRole";
        return item->data(index.column());
    }
    return QVariant();
}

bool CustomTreeItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //TreeModel::setData 是重写的父类函数，是在编辑完后会被自动调用的函数
    //TreeItem::setData 是自定义的函数，来真正修改数据
    if (index.isValid() && role == Qt::EditRole)
    {
        CustomTreeItem *item = static_cast<CustomTreeItem *>(index.internalPointer());
        item->setData(index.column(), value);
        emit dataChanged(index, index);
//        qDebug()<<"mkmk";
        return true;
    }
    return false;
}


CustomTreeItem *CustomTreeItemModel::itemFromIndex(const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;
    CustomTreeItem *item = static_cast<CustomTreeItem *>(index.internalPointer());
    return item;
}

QModelIndex CustomTreeItemModel::indexFromItem(CustomTreeItem *item)
{
    CustomTreeItem *tmp = item;
    QVector<CustomTreeItem *>itemVector;
    while (tmp->parentItem() != nullptr) {
        itemVector.push_back(item->parentItem());
        tmp = tmp->parentItem();
    }
    itemVector.push_back(item);
    QModelIndex tmpIndex;
    itemVector.erase(itemVector.begin());
    for (int i = 0; i < itemVector.size(); ++i) {
        // 遍历赋值，保证index的父节点都正确
        tmpIndex = index(itemVector[i]->row(), 0, tmpIndex);
    }
    return tmpIndex;
}

CustomTreeItem *CustomTreeItemModel::root()
{
    return mRootItem;
}


CustomFilterModel::CustomFilterModel(QObject *parent) : QSortFilterProxyModel (parent)
{

}
CustomFilterModel::~CustomFilterModel()
{
    delete keyWord;
}

bool CustomFilterModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    QModelIndex idx = sourceModel()->index(source_row, searchColumn, source_parent);
    CustomTreeItem *it = idx.data(Qt::UserRole).value<CustomTreeItem *>();
    if (it != nullptr) {
        QString origin = it->data(searchColumn).toString();
        qDebug() << "fffff" << origin;
        if (keyWord!=nullptr && origin.contains(keyWord)) {
            return true;
        }

        for (int row = 0 ; row <it->childCount() ; row++) {
            CustomTreeItem *childItem = it->child(row);
            qDebug() << "child:" << childItem->data(searchColumn).toString();
            if (keyWord!=nullptr && childItem->data(searchColumn).toString().contains(keyWord)) {
                return true;
            }
        }
    }

    return false;
}







