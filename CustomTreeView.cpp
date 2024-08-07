#include "CustomTreeView.h"
#include "ui_CustomTreeView.h"
#include <QTreeView>
#include <vector>
#include "CustomTreeItemModel.h"
#include <QRandomGenerator>
#include <QCheckBox>
#include "CustomTreeItemStyleDelegate.h"
#include <QAbstractItemModel>
#include "MyUtil.h"

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

    //mock数据
    QJsonArray schoolArr = MyUtil::getSchoolData();
    for (int i = 0 ; i < schoolArr.count() ; i++) {
        CustomTreeItem *school = new CustomTreeItem(root);
        QJsonObject schoolObj = schoolArr[i].toObject();
        QJsonArray stuArr = schoolObj["students"].toArray();
        QVector<QVariant> dataSchool;
        dataSchool << QString::number(i) << schoolObj["school"].toString() << "学生人数：" + QString::number(stuArr.count()) << QVariant::fromValue(new QCheckBox());
        school->setItemData(dataSchool);
        root->appendChild(school);
        for (int j = 0 ; j < stuArr.count() ; j++) {
            QJsonObject stuObj = stuArr[j].toObject();
            QVector<QVariant> dataStu;
            dataStu << stuObj["name"].toString() << stuObj["grade"].toString() + "级" << stuObj["gender"].toString() << QVariant::fromValue(new QCheckBox());
            CustomTreeItem *student = new CustomTreeItem(school);
            student->setItemData(dataStu);
            school->appendChild(student);

            QJsonObject scoreObj = stuObj["score"].toObject();
            QStringList subjects = scoreObj.keys();
            for (int k = 0 ; k < subjects.count() ; k++) {
                QVector<QVariant> dataScore;
                dataScore << QString::number(k) << subjects[k] << QString::number(scoreObj[subjects[k]].toInt()) + "分" << QVariant::fromValue(new QCheckBox());
                CustomTreeItem *score = new CustomTreeItem(student);
                score->setItemData(dataScore);
                student->appendChild(score);
            }
        }
    }

    //随机数据
//    QRandomGenerator *generator = QRandomGenerator::global();
//    for (int i = 0 ; i < 30 ; i++) {
//        CustomTreeItem *l1 = new CustomTreeItem(root);
//        QVector<QVariant> data1;
//        data1 << i << "School:" + QString::number(i+1) << "第" + QString::number(i) + "所学校" << QVariant::fromValue(new QCheckBox());
//        l1->setItemData(data1);
//        root->appendChild(l1);

//        for (int j = 0 ; j < 10 ; j++) {
//            CustomTreeItem *l2 = new CustomTreeItem(l1);
//            QVector<QVariant> data2;
//            int stuCount = generator->bounded(10,20);
//            data2 << j << "Teacher" + QString::number(j+1) << "学生人数：" + QString::number(stuCount) << QVariant::fromValue(new QCheckBox());
//            l2->setItemData(data2);
//            l1->appendChild(l2);

//            for (int k = 0 ; k < stuCount ; k++) {
//                CustomTreeItem *l3 = new CustomTreeItem(l2);
//                QVector<QVariant> data3;
//                data3 << k << "Student" + QString::number(k+1) << "Score:" + QString::number(generator->bounded(50,100)) << QVariant::fromValue(new QCheckBox());
//                l3->setItemData(data3);
//                l2->appendChild(l3);
//            }
//        }
//    }

    treeViewDelegate = new CustomTreeItemStyleDelegate(ui->treeView,this);
    ui->treeView->setItemDelegate(treeViewDelegate);
    ui->treeView->setModel(m_dataModel);

    m_filterModel = new CustomFilterModel(ui->treeView);

//    m_filterModel->keyWord = new QString("北京");
    m_filterModel->setSourceModel(m_dataModel);
    m_filterModel->setFilterKeyColumn(0);
    ui->filterTreeView->setModel(m_filterModel);
    ui->filterTreeView->setItemDelegate(new CustomTreeItemStyleDelegate(ui->filterTreeView,this));


}

void CustomTreeView::on_searchBtn_clicked()
{
    if (!treeViewDelegate) {
        return;
    }

    treeViewDelegate->mMatchWord = ui->lineEdit->text();
    ui->treeView->viewport()->update();
    m_filterModel->searchColumn = 0;
    m_filterModel->keyWord = new QString(ui->lineEdit->text());
    m_filterModel->invalidate();
    ui->filterTreeView->viewport()->update();
    ui->filterTreeView->expandAll();
}


void CustomTreeView::on_pushButton_clicked()
{
    if (!treeViewDelegate) {
        return;
    }
    treeViewDelegate->mMatchWord = ui->lineEdit->text();
    ui->treeView->viewport()->update();
    m_filterModel->searchColumn = 1;
    m_filterModel->keyWord = new QString(ui->lineEdit->text());
    m_filterModel->invalidate();
    ui->filterTreeView->viewport()->update();
    ui->filterTreeView->expandAll();
}




















