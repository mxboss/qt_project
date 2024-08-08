#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
//class QTcpSocket;
#include <QTcpServer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:
    void on_startServerBtn_clicked();
    void on_closeServerBtn_clicked();
    void on_pushButton_clicked();
    void on_sendBtn_clicked();


private:
    Ui::ServerWidget *ui;
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_tcpSocket = nullptr;
    QString getIPAddress();
    quint16 getPort();
    void resetSocket();
    void resetServer();
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // SERVERWIDGET_H
