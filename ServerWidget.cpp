#include "ServerWidget.h"
#include "ui_ServerWidget.h"
#include <QDebug>
#include <QTcpSocket>
#include <QKeyEvent>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
    ui->ipLE->setPlaceholderText("输入IP，默认IP："+getIPAddress());
}

ServerWidget::~ServerWidget()
{
    delete ui;
    if (m_tcpServer && m_tcpServer->isListening()) {
        m_tcpServer->close();
    }
    delete m_tcpServer;
}

QString ServerWidget::getIPAddress()
{
    return ui->ipLE->text().length() > 0 ? ui->ipLE->text():"192.168.0.112";
}

quint16 ServerWidget::getPort()
{
    return ui->portLE->text().length() > 0 ? ui->portLE->text().toUShort():0471;
}

void ServerWidget::on_startServerBtn_clicked()
{
    if (m_tcpServer == nullptr) {
        resetServer();
    }
    if (m_tcpServer->isListening()) {
        ui->reciveLE->append("服务器已经开启监听，请勿重复监听!!!");
        return;
    }
    //服务端开启监听
    if (m_tcpServer->listen(QHostAddress::Any,getPort())) {
        ui->reciveLE->append("服务器开启监听");
        qDebug()<<"serverPort:"<<m_tcpServer->serverPort();
        qDebug()<<"serverAddress:"<<m_tcpServer->serverAddress();
    } else {
        ui->reciveLE->append("服务器监听失败！！！");
    }
}

void ServerWidget::on_closeServerBtn_clicked()
{
    if (m_tcpServer == nullptr) {
        return;
    }
    m_tcpServer->close();
    m_tcpServer = nullptr;
    m_tcpSocket = nullptr;
    ui->reciveLE->append("服务器已关闭");
}


void ServerWidget::on_sendBtn_clicked()
{
    if (ui->sendLE->toPlainText().length() < 1) {
        return;
    }
    if (!m_tcpServer->isListening()) {
        ui->reciveLE->append("服务端不可用");
        return;
    }
    QTcpSocket* socket = m_tcpSocket;
    if (!socket) {
        ui->reciveLE->append("没有连接中的客户端");
        qDebug()<<"没有可用的客户端";
        return;
    }
    ui->reciveLE->append("我："+ ui->sendLE->toPlainText());
    socket->write(ui->sendLE->toPlainText().toUtf8());

    ui->sendLE->clear();
}

void ServerWidget::on_pushButton_clicked()
{
    ui->reciveLE->clear();
}

void ServerWidget::resetSocket()
{
    QObject::connect(m_tcpSocket,&QTcpSocket::readyRead,this,[this](){
        qDebug()<<"readyRead";
        if (m_tcpSocket) {
            QString text = m_tcpSocket->readAll();
            qDebug()<<"readyread"<<text;
            ui->reciveLE->append("signal:readyRead;接收数据：" + text);
        } else {
            qDebug()<<"无连接";
        }
    });
    QObject::connect(m_tcpSocket,&QTcpSocket::aboutToClose,this,[&](){
        qDebug()<<"close";
        m_tcpSocket = nullptr;
    });
    connect(m_tcpSocket,&QAbstractSocket::disconnected,this,[this](){
        qDebug()<<"disconnected";
        m_tcpSocket = nullptr;
        ui->reciveLE->append("客户端已断开");
    });
}

void ServerWidget::resetServer()
{
    m_tcpServer = nullptr;
    m_tcpServer = new QTcpServer(this);

    QObject::connect(m_tcpServer,&QTcpServer::newConnection,this,[=](){
        m_tcpSocket = m_tcpServer->nextPendingConnection();
        ui->reciveLE->append("signal:newConnection;新的连接,客户端:"+m_tcpSocket->peerAddress().toString()+"端口号："+QString::number(m_tcpSocket->peerPort()));
        m_tcpSocket->write("hello,client");
        resetSocket();
    });
    QObject::connect(m_tcpServer,&QTcpServer::acceptError,this,[](QAbstractSocket::SocketError socketError){
        qDebug() << socketError;
    });
}

void ServerWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        qDebug()<<"自定义回车";
        emit(on_sendBtn_clicked());
    }
}
