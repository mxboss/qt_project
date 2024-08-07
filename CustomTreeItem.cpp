#include "CustomTreeItem.h"

CustomTreeItem::CustomTreeItem(CustomTreeItem *parent)
{
    mParentItem = parent;
    mLevel = 0;
    mRow = 0;

}

CustomTreeItem::~CustomTreeItem()
{

}

void CustomTreeItem::appendChild(CustomTreeItem *child)
{
    child->setRow(mChildItems.size());
    child->setLevel(mLevel + 1);
    mChildItems.append(child);
    if (child->mLevel == 1) {
        //设置搜索key
        searchKey = child->itemData()[0].toString();
    } else {
        //将子元素的搜索key设置为跟父节点一致
        child->searchKey = searchKey;
    }
}

void CustomTreeItem::removeChilds()
{
    qDeleteAll(mChildItems);
    mChildItems.clear();
}

QVariant CustomTreeItem::data(int column) const
{
    if (column < mItemData.size()) {
        return mItemData[column];
    }
    return QVariant();
}

void CustomTreeItem::setData(int column, QVariant value)
{
    if (column >= mItemData.size()) {
        return;
    }
    mItemData[column] = value;
}

CustomTreeItem *CustomTreeItem::child(int row)
{
    return mChildItems.value(row);
}

CustomTreeItem *CustomTreeItem::parentItem()
{
    return mParentItem;
}

int CustomTreeItem::childCount() const
{
    return mChildItems.count();
}

int CustomTreeItem::row() const
{
    return mRow;
}

