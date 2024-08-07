#ifndef NETWORKSTUDYPANEL_H
#define NETWORKSTUDYPANEL_H

#include <QWidget>
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

namespace Ui {
class NetworkStudyPanel;
}

class NetworkStudyPanel : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkStudyPanel(QWidget *parent = nullptr);
    ~NetworkStudyPanel();

private slots:
    void on_pushButton_clicked();
    void doProcessReadyRead();

private:
    Ui::NetworkStudyPanel *ui;
    QNetworkAccessManager *netManager;
    QNetworkReply *reply;
    QNetworkRequest *request;

    void setupSubViews();
};

#endif // NETWORKSTUDYPANEL_H
