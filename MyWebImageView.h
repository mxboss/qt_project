#ifndef MYWEBIMAGEVIEW_H
#define MYWEBIMAGEVIEW_H
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <Qlabel>

class MyWebImageView : public QWidget
{
    Q_OBJECT

public:
    explicit MyWebImageView(QString* urlString, QWidget *parent = nullptr);
    ~MyWebImageView();
public slots:
    void imageDownloadFinished();
private:
    QLabel *m_label;
    QString m_url;
    QNetworkAccessManager *m_manager;
    QNetworkRequest *m_request;
    QNetworkReply *m_reply;
};

#endif // MYWEBIMAGEVIEW_H
