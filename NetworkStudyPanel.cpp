#include "NetworkStudyPanel.h"
#include "ui_NetworkStudyPanel.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkReply>
#include <QSslSocket>


NetworkStudyPanel::NetworkStudyPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkStudyPanel)
{
    ui->setupUi(this);
    netManager = new QNetworkAccessManager(this);
    setupSubViews();

    qDebug() << "NENENENENENE";
    connect(netManager, &QNetworkAccessManager::finished, this, [&](){
        qDebug() << "END";
    });

    qDebug() << QSslSocket::sslLibraryBuildVersionString();

    // 连接错误信号
//    QObject::connect(reply, &QNetworkReply::error, [&](QNetworkReply::NetworkError error) {
//        qDebug() << "Error occurred:" << error;
//    });

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


void NetworkStudyPanel::on_pushButton_clicked()
{
    qDebug() << "SSL support:" << QSslSocket::supportsSsl();
    qDebug() << "OpenSSL version:" << QSslSocket::sslLibraryVersionString();
    qDebug() << "OpenSSL version number:" << QSslSocket::sslLibraryVersionNumber();
//    return;
//    // 创建网络访问管理器
//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

//    // 创建请求
//    QNetworkRequest request(QUrl("https://dog.ceo/api/breed/pembroke/images/random"));
////    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

//    // 发起HTTPS GET请求
//    QNetworkReply *reply = manager.get(request);

//    // 连接信号以处理响应
//    QObject::connect(reply, &QNetworkReply::finished, [&]() {
//        if (reply->error() == QNetworkReply::NoError) {
//            qDebug() << "HTTPS request succeeded!";
//            qDebug() << "Response:" << reply->readAll();
//        } else {
//            qDebug() << "HTTPS request failed with error:" << reply->errorString();
//        }
////        reply->deleteLater();
//    });
//    QObject::connect(reply,&QIODevice::readyRead, this, &NetworkStudyPanel::doProcessReadyRead);

    QNetworkRequest req(QUrl("https://dog.ceo/api/breed/pembroke/images/random"));
    netManager->get(req);
//    QObject::connect(netManager, SIGNAL(readyRead()) ,this, &NetworkStudyPanel::doProcessReadyRead);
//    QObject::connect(reply,&QIODevice::readyRead, this, &NetworkStudyPanel::doProcessReadyRead);

//        connect(reply,SIGNAL(readyRead()),this,SLOT(doProcessReadyRead()));//数据来临的信号，IO操作大多数都是这个信号
//        connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(doProcessError(QNetworkReply::NetworkError)));
//        connect(reply,SIGNAL(finished()),this,SLOT(doProcessFinished()));//传输（一次应答）完成
//        //会将总文件长度，和当前文件传输长度反馈到参数中，正适合做进度条
//        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(doProcessDownload(qint64,qint64)));

//        QStringList list = url_str.split("/");
//        QString filename = list.at(list.length()-1);
//        myFile->setFileName(filename);
//        bool ret = myFile->open(QIODevice::WriteOnly|QIODevice::Truncate);//以重写的方式打开，在写入新的数据时会将原有
//                                                                            //数据全部清除，游标设置在文件开头。
//        ui->progressBar->setValue(0);
//        ui->progressBar->setMinimum(0);
//    ————————————————

//                                Designed by Jack Chen

//    原文链接：https://blog.csdn.net/weixin_40615338/article/details/122343555
}
