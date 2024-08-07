#include "StudentTreeWidget.h"
#include <QDebug>
#include <QTreeWidget>
#include "MyUtil.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QJsonObject>

StudentTreeWidget::StudentTreeWidget(QWidget *parent) : QWidget(parent)
{
   m_dataList = new QJsonArray(MyUtil::getSchoolData());
   qDebug() << m_dataList;
   setUpUi();
   resize(300,500);
}

StudentTreeWidget::StudentTreeWidget(QJsonArray *dataList,QWidget *parent) : QWidget(parent),
    m_dataList(new QJsonArray(*dataList))
{
    qDebug() << *dataList;

}

void StudentTreeWidget::setUpUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    QLabel *label = new QLabel("学生信息汇：");
    label->setFont(QFont("微软雅黑",25,QFont::Bold));
    layout->addWidget(label);

    QTreeWidget *treeWidget = new QTreeWidget(this);
    QStringList topItemList{"学校","地区"};
    treeWidget->setColumnCount(1);
    treeWidget->header()->hide();
    treeWidget->addTopLevelItem(new QTreeWidgetItem(topItemList));
    treeWidget->setFont(QFont("宋体",22,QFont::Bold));

    //创建子项
    QTreeWidgetItem *topSchoolItem = treeWidget->itemAt(0,0);

    for(int i = 0 ; i < (*m_dataList).count() ; i++) {
        QJsonValue v = (*m_dataList)[i];
        QJsonObject obj = v.toObject();
        QTreeWidgetItem *schoolItem = new QTreeWidgetItem(topSchoolItem);
        schoolItem->setText(0,obj["school"].toString());
        schoolItem->setFont(0,QFont("宋体",18,QFont::Normal));
        qDebug() << obj["school"];
        QJsonArray students = obj["students"].toArray();
        for (int j = 0 ; j < students.count() ; j++) {
            QJsonObject stuObj = students[j].toObject();
            QTreeWidgetItem *stuNameItem = new QTreeWidgetItem(schoolItem);
            stuNameItem->setText(0,stuObj["name"].toString());
            stuNameItem->setFont(0,QFont("宋体",16,QFont::Normal));
            QJsonObject scores = stuObj["score"].toObject();

            for (QString subjectName : scores.keys()) {
                QString score = QString::number(scores[subjectName].toInt());
                QTreeWidgetItem *scoreItem = new QTreeWidgetItem(stuNameItem);
                scoreItem->setText(0, subjectName+":"+score);
                scoreItem->setFont(0,QFont("宋体",14,QFont::Light));
//                stuNameItem->addChild(scoreItem);
            }
        }
    }
    layout->addWidget(treeWidget);
    treeWidget->resizeColumnToContents(0);
}


















