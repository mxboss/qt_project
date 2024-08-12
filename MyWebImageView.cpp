#include "MyWebImageView.h"
#include <QDebug>

MyWebImageView::MyWebImageView(QString* urlString, QWidget *parent) : QWidget(parent),
    m_url(*urlString),m_label(new QLabel)
{
    qDebug() << "img-link:" <<m_url;
    m_label->setParent(this);
    m_label->resize(200,200);
    m_label->setStyleSheet("background-color:red");
    m_manager = new QNetworkAccessManager(this);
    m_request = new QNetworkRequest(QUrl(m_url));
    m_request->setTransferTimeout(3000);
    m_reply = m_manager->get(*m_request);

    connect(m_reply,SIGNAL(finished()),this,SLOT(imageDownloadFinished()));
}

MyWebImageView::~MyWebImageView()
{
    delete m_manager;
    delete m_request;
    delete m_reply;
}

void MyWebImageView::imageDownloadFinished()
{
    QNetworkReply *reply = m_reply;
    // 获取响应状态码，200表示正常
    QVariant nCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug() << "image load finished,code:" << nCode.toInt();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        pixmap = pixmap.scaled(m_label->geometry().size(),Qt::KeepAspectRatio);
        m_label->setPixmap(pixmap);
    }
    else
    {
        // 错误处理-显示错误信息，或显示上一次缓存的图片或叉图。
        m_label->setText("下载失败");
    }

}
