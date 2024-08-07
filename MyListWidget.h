#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H
#include <QWidget>
#include <QJsonArray>
#include <QStyledItemDelegate>
#include <QPainter>

class MyListWidgetStyleDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MyListWidgetStyleDelegate(QWidget *parent = nullptr) : QStyledItemDelegate(parent) {

    }

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override{
        return QSize(200,44);
    }
};

class MyListWidget : public QWidget
{
    Q_OBJECT

public:
    MyListWidget(QWidget *parent = nullptr);
    ~MyListWidget();

private:
    QJsonArray m_dataArr;
    void setUpUI();
    QJsonArray getStudentList(QString& school);
};

#endif // MYLISTWIDGET_H
