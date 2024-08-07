#ifndef SINGLETON_H
#define SINGLETON_H

#include <QDebug>
#include <QJsonArray>

class Singleton
{
public:
    QJsonArray *homeData;
    static Singleton& shareInstance(){
        static Singleton instance;
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&)= delete ;

private:
    Singleton(){
        qDebug() << "singleton init";
    }
    ~Singleton(){
        qDebug() << "singleton destroyed";
    }

};

#endif // SINGLETON_H
