#ifndef CUSTOMTREEITEM_H
#define CUSTOMTREEITEM_H

#include <QVariant>

class CustomTreeItem
{
public:
    QString searchKey;


    explicit CustomTreeItem(CustomTreeItem *parent = nullptr);
    ~CustomTreeItem();
    void appendChild(CustomTreeItem *child);
    void removeChilds();                    // 清空所有节点
    CustomTreeItem *child(int row);
    CustomTreeItem *parentItem();
    int childCount() const;
    int row() const;
    //核心函数：获取节点第column列的数据
    QVariant data(int column) const;
    //修改节点内容(只对有数据的节点可修改，比如姓名、三门课，其他是根据这些内容自动求解的，会自动刷新)
    void setData(int column, QVariant value);

    //保存该节点是其父节点的第几个子节点，查询优化所用
    void setRow(int row) {
        mRow = row;
    }
    void setItemData(QVector<QVariant> data) {
        mItemData = data;
    }
    void setLevel(int level) {
        mLevel = level;
    }

    //获取数据
    QVector<QVariant> itemData() {
        return mItemData;
    }

private:
    CustomTreeItem *mParentItem; //父节点
    QList<CustomTreeItem *> mChildItems; //子节点
    int mLevel; //层级
    int mRow;   //所在行数
    QVector<QVariant> mItemData;    //数据
};

Q_DECLARE_METATYPE(CustomTreeItem *)

#endif // CUSTOMTREEITEM_H
