#ifndef CONTENTCELL_H
#define CONTENTCELL_H

#include <QWidget>
class QString;

namespace Ui {
class ContentCell;
}

struct ContentCellModel {
    QString title;
    QString content;
    QString typeDesc;
    int type;
};

class ContentCell : public QWidget
{
    Q_OBJECT

public:
    explicit ContentCell(QWidget *parent = nullptr);
    ~ContentCell();
    Ui::ContentCell *ui;
    void setModel(ContentCellModel& model);

private:
    ContentCellModel dataModel;

protected:


    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // CONTENTCELL_H
