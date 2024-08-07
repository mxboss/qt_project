#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H

#include <QWidget>
class CustomTreeItemModel;
class CustomTreeItemStyleDelegate;
class CustomFilterModel;

namespace Ui {
class CustomTreeView;
}

class CustomTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomTreeView(QWidget *parent = nullptr);
    ~CustomTreeView();

private slots:
    void on_loadBtn_clicked();

    void on_searchBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::CustomTreeView *ui;
    void setUpSubViews();
    CustomTreeItemModel *m_dataModel = nullptr;
    CustomFilterModel *m_filterModel = nullptr;
    CustomTreeItemStyleDelegate *treeViewDelegate = nullptr;
};

#endif // CUSTOMTREEVIEW_H
