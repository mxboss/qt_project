#include "ContentCell.h"
#include "ui_ContentCell.h"
#include <QPainter>
#include <QDebug>
#include <memory>
#include "MyListWidget.h"
#include "StudentTreeWidget.h"
#include "ScoreTableWidget.h"
#include "MyUtil.h"
#include <QString>
#include "NetworkStudyPanel.h"
#include "CustomTreeView.h"
#include "ServerWidget.h"

ContentCell::ContentCell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentCell)
{
    ui->setupUi(this);
}

ContentCell::~ContentCell()
{
    delete ui;
}

void ContentCell::setModel(ContentCellModel& model)
{
    dataModel = ContentCellModel(model);
    ui->titleLabel->setText(dataModel.title);
    ui->midLabel->setText(dataModel.content);
    ui->bottomLabel->setText(dataModel.typeDesc);
}

void ContentCell::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // 设置反锯齿以获得平滑的边缘
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置笔（边框）
    QPen pen(Qt::black, 0.5); // 黑色，宽度为2
    painter.setPen(pen);

    // 设置刷子（填充）
    QBrush brush(Qt::white); // 蓝色填充
    painter.setBrush(brush);

    // 绘制圆角矩形
//    QRect rect(50, 50, 200, 100); // 矩形位置和大小
    int cornerRadius = 10; // 圆角半径
    painter.drawRoundedRect(this->rect(), cornerRadius, cornerRadius);
//    painter.fillRect(this->rect(), Qt::white);
    QWidget::paintEvent(event);
}

void ContentCell::mousePressEvent(QMouseEvent *event) {
    qDebug() << dataModel.type;
    if (dataModel.type == 1) {
        MyListWidget *listWidget = new MyListWidget();
        listWidget->show();
    } else if (dataModel.type == 3) {
        StudentTreeWidget *treeWidget = new StudentTreeWidget();
        treeWidget->show();
    } else if (dataModel.type == 2) {
        QString school = "中国人民大学";
        QJsonArray stuLisit = MyUtil::getStudentList(school);
        ScoreTableWidget *scoreWidget = new ScoreTableWidget(&school,&stuLisit);
        scoreWidget->show();
    } else if (dataModel.type == 4) {
        // 网络加载图片
        NetworkStudyPanel *panel = new NetworkStudyPanel();
        panel->show();
    } else if (dataModel.type == 5) {
        //自定义TreeView
        CustomTreeView *view = new CustomTreeView();
        view->show();
    } else if (dataModel.type == 6) {
        //网络模拟
        ServerWidget *view = new ServerWidget();
        view->show();
    }
    QWidget::mousePressEvent(event);
}
