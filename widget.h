#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}
class QJsonArray;
class QLayout;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QPixmap getPixmapWithBorderRadius(const QPixmap& pixmap,int radius);
    QJsonArray *dataList;
    void buildCenterView(QJsonArray& data);
    void clearLayout(QLayout& layout);
};

#endif // WIDGET_H
