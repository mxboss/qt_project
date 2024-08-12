#include "LeftNaviListView.h"
#include <QDebug>
#include <QJsonObject>
#include <QFile>
#include <QStandardItemModel>
#include <LeftNaviListWidgetDelegate.h>
#include <QJsonDocument>
#include <QStringListModel>
#include "singleton.h"
#include <ui_widget.h>

LeftNaviListView::LeftNaviListView(QWidget *parent):QListView{parent},ui(new Ui::Widget)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
//    QFile file(":/my/mock/home_page.json");
//    if(file.open(QIODevice::ReadOnly)) {
//        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
//        QJsonArray arr = jsonDoc.array();
//        Singleton::shareInstance().homeData = arr;

    //使用standardItemModel
//        QStandardItemModel *itemModel = new QStandardItemModel();
//        for (int i = 0 ; i < arr.count() ; i++) {
//            auto obj = arr[i];
//            qDebug() << obj;
//            QJsonObject model = obj.toObject();
//            QStandardItem *item = new QStandardItem();
//            item->setData(model["title"].toString(),Qt::DisplayRole);
//            itemModel->appendRow(item);
//        }
//        setModel(itemModel);

    //使用StringListModel
//        QStringListModel *listModel = new QStringListModel(this);
//        QStringList *strinList = new QStringList();
//        for(auto obj:arr) {
//            QJsonObject model = obj.toObject();
//            strinList->append(model["title"].toString());
//        }
//        listModel->setStringList(*strinList);
//        file.close();
//        setModel(listModel);
//    }
    m_dataList = new QJsonArray();
    delegate = new LeftNaviListWidgetDelegate(this);
    setItemDelegate(delegate);
}


LeftNaviListView::~LeftNaviListView()
{
    qDebug() << "~LeftNaviListView";
    delete m_dataList;
}

QJsonArray* LeftNaviListView::dataList() const
{
    qDebug() << "read dataList";
    return m_dataList;
}

void LeftNaviListView::setDataList(QJsonArray* dataList)
{
    qDebug() << dataList << Singleton::shareInstance().homeData;
    if (m_dataList != nullptr && *m_dataList == *dataList) {
        return;
    }
    if (m_dataList != nullptr) {
        qDebug() << "ori data:" << m_dataList ;
        delete m_dataList;
    }
    qDebug() << "setDataList";
    QJsonArray *newArr = new QJsonArray(*dataList);
    qDebug() << "newArr:" << newArr;
    m_dataList = newArr;
    qDebug() << m_dataList << newArr;
    emit dataListDidChanged();
    QStringListModel *model = new QStringListModel(this);
    QStringList *list = new QStringList();
    QJsonArray tmp = QJsonArray(*m_dataList);
    for(auto obj : tmp) {
        QJsonObject o = obj.toObject();
        list->append(o["title"].toString());
    }
    model->setStringList(*list);
    qDebug() << *list;
    setModel(model);
}
