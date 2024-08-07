#ifndef CUSTOMTREEITEMSTYLEDELEGATE_H
#define CUSTOMTREEITEMSTYLEDELEGATE_H

#include <QStyledItemDelegate>

class QTreeView;

class CustomTreeItemStyleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomTreeItemStyleDelegate(QTreeView *view,QWidget *parent = nullptr);
    ~CustomTreeItemStyleDelegate();

//    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        return QSize(20,50);
    }

    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;


    QString mMatchWord = "";
    private:
    QTreeView *m_treeView;

    QStringList SpliteWord(QString originWord) const;
    void DrawKeyword(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // CUSTOMTREEITEMSTYLEDELEGATE_H
