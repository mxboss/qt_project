#ifndef STUDENTTREEWIDGET_H
#define STUDENTTREEWIDGET_H

#include <QWidget>
#include <QJsonArray>

class StudentTreeWidget : public QWidget
{
    Q_OBJECT
public:
    StudentTreeWidget(QWidget *parent = nullptr);
    StudentTreeWidget(QJsonArray *dataList,QWidget *parent = nullptr);

private:
    QJsonArray *m_dataList;
    void setUpUi();
signals:

public slots:

};

#endif // STUDENTTREEWIDGET_H
