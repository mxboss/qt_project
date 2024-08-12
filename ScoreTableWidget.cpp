#include "ScoreTableWidget.h"
#include <QDebug>
#include <QTableWidget>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QLabel>

ScoreTableWidget::ScoreTableWidget(QString *school,QJsonArray *dataArr, QWidget *parent) : QWidget (parent),
    m_dataArr(new QJsonArray(*dataArr)),m_school(new QString(*school))
{
    qDebug() << "m_dataArr:" << m_dataArr;
    setUpUi();
    resize(600,500);
}

ScoreTableWidget::~ScoreTableWidget()
{

}

void ScoreTableWidget::setUpUi()
{
    int row = m_dataArr->count();
    QJsonObject firstValue = m_dataArr->first().toObject();
    QJsonObject subjects = firstValue["score"].toObject();
    int column = subjects.keys().count();

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    QLabel *label = new QLabel(*m_school + QString("学生分数："));
    label->setFont(QFont("微软雅黑",25,QFont::Bold));
    layout->addWidget(label);

    QTableWidget *widget = new QTableWidget(row,column,this);
    widget->setFont(QFont("宋体",16,QFont::Normal));
    QStringList subjectTitle;
    for (QString v : subjects.keys()) {
        subjectTitle.append(v.toUpper());
    }
    widget->setHorizontalHeaderLabels(subjectTitle);

    QStringList nameList;

    for (int i = 0 ; i < m_dataArr->count() ; i++) {
        QJsonValue v = (*m_dataArr)[i];
        QJsonObject obj = v.toObject();
        QString name = obj["name"].toString();
        nameList.append(name);
        QJsonObject scoreObj = obj["score"].toObject();

        for (int j = 0 ; j < subjects.keys().count() ; j++) {
            QString sub = subjects.keys()[j];
            int score = scoreObj[sub].toInt();
            qDebug() << i << "," << j << sub << score;
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(score));
            item->setSizeHint(QSize(80,44));
            widget->setItem(i,j,item);
        }
    }
    widget->setVerticalHeaderLabels(nameList);
    qDebug() << nameList;

    layout->addWidget(widget);
}
