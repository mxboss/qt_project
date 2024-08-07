#ifndef MYUTIL_H
#define MYUTIL_H
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

namespace MyUtil {


QJsonArray getSchoolData();
QJsonArray getStudentList(QString& school);

}


#endif // MYUTIL_H
