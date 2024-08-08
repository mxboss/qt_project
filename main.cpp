#include "widget.h"
#include <QApplication>
#include <QCoreApplication>
#include <QTimer>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
//    QCoreApplication app(argc, argv);

//    QTimer::singleShot(2000, [](){
//        qDebug() << "Hello from the backend!";
//        QCoreApplication::quit();
//    });

//    return app.exec();
}
