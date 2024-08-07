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

#include <QSortFilterProxyModel>

class CustomFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    CustomFilterModel(QObject *parent = nullptr);
    ~CustomFilterModel();

    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
    int searchColumn = 0;
    QString *keyWord = nullptr;
};

#endif // CUSTOMTREEITEMMODEL_H
