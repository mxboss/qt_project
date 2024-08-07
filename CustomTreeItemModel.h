#ifndef CUSTOMTREEITEMMODEL_H
#define CUSTOMTREEITEMMODEL_H

#include <QAbstractItemModel>
#include <QSize>
#include "CustomTreeItem.h"

class CustomTreeItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit CustomTreeItemModel(QStringList headers,QObject *parent = nullptr);
    ~CustomTreeItemModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;


    CustomTreeItem *itemFromIndex(const QModelIndex &index) const;
    QModelIndex indexFromItem(CustomTreeItem *item);
    CustomTreeItem *root();
    QSize ss;
private:
    QStringList mHeaders;   // 表头内容
    CustomTreeItem *mRootItem;    // 根节点
};

#endif // CUSTOMTREEITEMMODEL_H
