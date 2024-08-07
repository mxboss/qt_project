#include "widget.h"
#include "ui_widget.h"

#include <QBitmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QFile>
#include "singleton.h"
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "ContentCell.h"
#include "ui_ContentCell.h"
#include <QGridLayout>
#include <QLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("样式库");

    QPixmap pixmap = QPixmap(":/my/image/monkey_sun.jpg");
    pixmap = pixmap.scaled(60,60,Qt::KeepAspectRatio);
    pixmap = getPixmapWithBorderRadius(pixmap, 30);
    ui->avatorImageView->setPixmap(pixmap);

    //解析数据
    QFile file(":/my/mock/home_page.json");

    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
        dataList = new QJsonArray(jsonDoc.array());
        Singleton::shareInstance().homeData = new QJsonArray(*dataList);

        //LeftNavigation左侧导航listView
        ui->leftListView->setDataList(dataList);
        file.close();
    }

    //绑定左侧导航栏点击
    QObject::connect(ui->leftListView,&QListView::clicked,this,[&](const QModelIndex &index){
        qDebug() << index.model()->data(index,Qt::DisplayRole);
        QString title = index.model()->data(index,Qt::DisplayRole).toString();
        ui->titleLabel->setText(title);

        QJsonValue subobj = (*dataList)[index.row()];
        qDebug() << subobj;
        if (subobj.isObject()){
            QJsonArray list = subobj["subClass"].toArray();
            qDebug() << list;
            this->buildCenterView(list);
        } else {
            qDebug() << "非法数据";
        }
    });
}

void Widget::buildCenterView(QJsonArray& data)
{
    clearLayout(*ui->gridLayout);
    for (int i = 0; i < data.count(); i ++) {
        QJsonValue obj = data[i];
        qDebug() << obj;
        if (obj.isObject()) {
            ContentCellModel model {obj["title"].toString(),obj["content"].toString(),obj["typeDesc"].toString(),obj["type"].toInt()};
            ContentCell *cell = new ContentCell(this);
            cell->setModel(model);
            int column = (i+2) % 2;
            int row = i / 2;
            qDebug() << row << "," << column;
            ui->gridLayout->addWidget(cell,row,column,Qt::AlignLeft | Qt::AlignTop);
        }
    }
}

void Widget::clearLayout(QLayout& layout)
{
    while (QLayoutItem *item = layout.takeAt(0)) {
        if (QWidget *w = item->widget()) {
            w->deleteLater();
        }
        delete item;
    }
}


Widget::~Widget()
{
    delete ui;
    delete dataList;
}

QPixmap Widget::getPixmapWithBorderRadius(const QPixmap& pixmap, int radius)
{
    QPixmap resultPixmap = pixmap;
    QBitmap mask(pixmap.size());

    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::color1);

    painter.drawRoundedRect(0,0,pixmap.width(),pixmap.height(),radius,radius);

    resultPixmap.setMask(mask);
    return resultPixmap;
}


