#ifndef SCORETABLEWIDGET_H
#define SCORETABLEWIDGET_H

#include <QWidget>
#include <QJsonArray>


class ScoreTableWidget : public QWidget
{
public:
    explicit ScoreTableWidget(QString *school, QJsonArray *dataArr, QWidget *parent = nullptr);
    ~ScoreTableWidget();

private:
    QJsonArray *m_dataArr;
    QString *m_school;
    void setUpUi();
};

#endif // SCORETABLEWIDGET_H
