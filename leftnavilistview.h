#ifndef LEFTNAVILISTVIEW_H
#define LEFTNAVILISTVIEW_H

#include <QWidget>
#include <QListView>
namespace Ui {
class Widget;
}

class QJsonArray;
class QStandardItemModel;
class LeftNaviListWidgetDelegate;

class LeftNaviListView : public QListView
{
    Q_OBJECT
    Q_PROPERTY(QJsonArray* dataList READ dataList WRITE setDataList NOTIFY dataListDidChanged)

public:
    explicit LeftNaviListView(QWidget *parent = nullptr);
    ~LeftNaviListView();

    Ui::Widget *ui;
    QJsonArray *dataList() const;
    void setDataList(QJsonArray *data);

signals:
    void dataListDidChanged();

private:
    QJsonArray *m_dataList;
    QStandardItemModel *standardModel;
    LeftNaviListWidgetDelegate *delegate;


};

#endif // LEFTNAVILISTVIEW_H
