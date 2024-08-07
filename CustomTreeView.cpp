#include "CustomTreeView.h"
#include "ui_CustomTreeView.h"
#include <QTreeView>
#include <vector>
#include "CustomTreeItemModel.h"
#include <QRandomGenerator>
#include <QCheckBox>
#include "CustomTreeItemStyleDelegate.h"
#include <QAbstractItemModel>

CustomTreeView::CustomTreeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomTreeView)
{
    ui->setupUi(this);
    setUpSubViews();
    resize(1000,600);
}

CustomTreeView::~CustomTreeView()
{
    delete ui;
}

void CustomTreeView::setUpSubViews()
{

}

void CustomTreeView::on_loadBtn_clicked()
{
    //加载model
    QStringList headList;
    headList << "ID" << "NAME" << "Desc" << "Status";
    m_dataModel = new CustomTreeItemModel(headList,ui->treeView);
    CustomTreeItem *root = m_dataModel->root();

    QRandomGenerator *generator = QRandomGenerator::global();
    for (int i = 0 ; i < 30 ; i++) {
        CustomTreeItem *l1 = new CustomTreeItem(root);
        QVector<QVariant> data1;
        data1 << i << "School:" + QString::number(i+1) << "第" + QString::number(i) + "所学校" << QVariant::fromValue(new QCheckBox());
        l1->setItemData(data1);
        root->appendChild(l1);

        for (int j = 0 ; j < 10 ; j++) {
            CustomTreeItem *l2 = new CustomTreeItem(l1);
            QVector<QVariant> data2;
            int stuCount = generator->bounded(10,20);
            data2 << j << "Teacher" + QString::number(j+1) << "学生人数：" + QString::number(stuCount) << QVariant::fromValue(new QCheckBox());
            l2->setItemData(data2);
            l1->appendChild(l2);

            for (int k = 0 ; k < stuCount ; k++) {
                CustomTreeItem *l3 = new CustomTreeItem(l2);
                QVector<QVariant> data3;
                data3 << k << "Student" + QString::number(k+1) << "Score:" + QString::number(generator->bounded(50,100)) << QVariant::fromValue(new QCheckBox());
                l3->setItemData(data3);
                l2->appendChild(l3);
            }
        }
    }

    treeViewDelegate = new CustomTreeItemStyleDelegate(ui->treeView,this);
    ui->treeView->setItemDelegate(treeViewDelegate);
    ui->treeView->setModel(m_dataModel);
//    ui->treeView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

//    ui->treeView->setst
}

void CustomTreeView::on_searchBtn_clicked()
{
    if (!treeViewDelegate) {
        return;
    }
    treeViewDelegate->mMatchWord = ui->lineEdit->text();
    ui->treeView->viewport()->update();
}





















