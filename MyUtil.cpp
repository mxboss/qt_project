#include "MyUtil.h"

QJsonArray MyUtil::getSchoolData() {
    QJsonArray arr;
    QFile file(":/my/mock/school.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
        arr = jsonDocument.array();
        file.close();
    }
    return arr;
}

QJsonArray MyUtil::getStudentList(QString& school)
{
    QJsonArray arr;
    QJsonArray data = MyUtil::getSchoolData();
    for (QJsonValue v : data) {
        QJsonObject obj = v.toObject();
        if (obj["school"].toString() == school) {
            arr = obj["students"].toArray();
        }
    }

    return arr;
}

