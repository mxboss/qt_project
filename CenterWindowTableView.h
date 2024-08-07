#ifndef CENTERWINDOWTABLEVIEW_H
#define CENTERWINDOWTABLEVIEW_H

#include <QTableWidget>

namespace Ui {
class Widget;
}

class CenterWindowTableView : public QTableWidget
{
    Q_OBJECT

public:
    CenterWindowTableView(QWidget *parent = nullptr);
private:
    Ui::Widget *ui;
};

#endif // CENTERWINDOWTABLEVIEW_H
