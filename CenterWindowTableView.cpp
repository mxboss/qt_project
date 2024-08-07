#include "CenterWindowTableView.h"
#include "ui_widget.h"
#include <QtDebug>

CenterWindowTableView::CenterWindowTableView(QWidget *parent) : QTableWidget(parent),
    ui(new Ui::Widget)
{
    qDebug() << "init TableWidget";

    setRowCount(2);
    setColumnCount(2);

//    setHorizontalHeaderLabels({"列1","列2"});
    setItem(0,0,new QTableWidgetItem("ListView"));
    setItem(0,1,new QTableWidgetItem("TableView"));
    setItem(1,0,new QTableWidgetItem("TreeView"));
    setItem(1,1,new QTableWidgetItem("TreeView"));
    resizeColumnsToContents();
}
