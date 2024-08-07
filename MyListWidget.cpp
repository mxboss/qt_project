#include "MyListWidget.h"
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QStringList>
#include <QListWidget>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include "ScoreTableWidget.h"
#include <QJsonObject>
#include "MyUtil.h"

MyListWidget::MyListWidget(QWidget *parent) : QWidget(parent)
{
    QFile file(":/my/mock/school.json");
    if (file.open(QIODevice::ReadOnly)) {
        m_dataArr= QJsonDocument::fromJson(file.readAll()).array();
        file.close();
        setUpUI();
    } else {
        qDebug() << "errJson";
    }

    resize(340,600);

}

MyListWidget::~MyListWidget()
{

}

QJsonArray MyListWidget::getStudentList(QString& school)
{
    QJsonArray arr;
    for (QJsonValue v : m_dataArr) {
        QJsonObject obj = v.toObject();
        if (obj["school"].toString() == school) {
            arr = obj["students"].toArray();
        }
    }
    qDebug() << arr;
    return arr;
}

void MyListWidget::setUpUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    QLabel *titleL = new QLabel("学校：");
    titleL->setFont(QFont("微软雅黑",24,2));
    layout->addWidget(titleL);

    QListWidget *listWidget = new QListWidget(this);
    listWidget->setFont(QFont("微软雅黑",18,QFont::Bold));
    listWidget->setItemDelegate(new MyListWidgetStyleDelegate(listWidget));
    for (QJsonValue obj : m_dataArr) {
        QString school;
        if (obj.isObject()) {
            school = obj["school"].toString().length() > 0 ? obj["school"].toString() : "Wrong Name";
        }
        listWidget->addItem(school);
    }
    layout->addWidget(listWidget);

    connect(listWidget,&QAbstractItemView::clicked,this,[&](const QModelIndex& index){
       qDebug() << index.model()->itemData(index).value(0).toString();
    });
    connect(listWidget,&QAbstractItemView::doubleClicked,this,[&](const QModelIndex& index){
        QString value = index.model()->itemData(index).value(0).toString();
        QJsonArray students = MyUtil::getStudentList(value);
        ScoreTableWidget *widget = new ScoreTableWidget(&value,&students);
        qDebug() << "students" << &students;
        widget->show();
    });
}
