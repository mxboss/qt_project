#include "NetworkStudyPanel.h"
#include "ui_NetworkStudyPanel.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QSslSocket>
#include <QLabel>
#include "MyWebImageView.h"
#include <QJsonObject>
#include <QJsonDocument>

NetworkStudyPanel::NetworkStudyPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkStudyPanel)
{
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);
    setupSubViews();
}

NetworkStudyPanel::~NetworkStudyPanel()
{
    delete ui;
}

void NetworkStudyPanel::setupSubViews()
{

}

void NetworkStudyPanel::doProcessReadyRead()
{
    //读取应答数据，并且写入文件中
    while(!reply->atEnd()){
        QByteArray ba = reply->readAll();
        qDebug() << ba;
    }
}

void NetworkStudyPanel::updateDogsView(QString* url)
{
    MyWebImageView *imgView = new MyWebImageView(url,this);

    ui->gridLayout->addWidget(imgView);
}


void NetworkStudyPanel::on_pushButton_clicked()
{
    // QString imgu("https://images.dog.ceo/breeds/pembroke/n02113023_6015.jpg");
    // updateDogsView(&imgu);
    // return;
    qDebug() << "sslLibraryBuildVersionString:" << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "SSL support:" << QSslSocket::supportsSsl();
    qDebug() << "OpenSSL version:" << QSslSocket::sslLibraryVersionString();
    qDebug() << "OpenSSL version number:" << QSslSocket::sslLibraryVersionNumber();

    // 创建请求
    // QNetworkRequest request(QUrl("https://dog.ceo/api/breed/pembroke/images/random"));
    QNetworkRequest *request = new QNetworkRequest(QUrl("https://dog.ceo/api/breed/pembroke/images/random"));
    // request.setRawHeader("User-Agent", "MyQTAgent Example");
    request->setTransferTimeout(5000);
    // 发起HTTPS GET请求
    QNetworkReply *reply = netManager->get(*request);

    connect(reply,&QNetworkReply::socketStartedConnecting,this,[](){
        qDebug() << "startSocketConnecting";
    });
    // 连接信号以处理响应
    QObject::connect(reply, &QNetworkReply::finished,this, [this,reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "HTTPS request succeeded!";
            qDebug() << "Response:" << reply->readAll();
            QJsonObject data = QJsonDocument::fromJson(reply->readAll()).object();
            QString imgurl = data["message"].toString();
            updateDogsView(&imgurl);
        } else {
            qDebug() << "HTTPS request failed with error:" << reply->errorString();
        }
        //        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::errorOccurred,[](QNetworkReply::NetworkError error){
        qDebug() << "errorOccurred" << error;
    });
}
