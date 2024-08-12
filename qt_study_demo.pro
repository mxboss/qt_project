#-------------------------------------------------
#
# Project created by QtCreator 2024-07-19T10:43:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_study_demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        CenterWindowTableView.cpp \
        ContentCell.cpp \
        CustomTreeItem.cpp \
        CustomTreeItemModel.cpp \
        CustomTreeItemStyleDelegate.cpp \
        CustomTreeView.cpp \
        LeftNaviListView.cpp \
        LeftNaviListWidgetDelegate.cpp \
        MyListWidget.cpp \
        MyUtil.cpp \
        MyWebImageView.cpp \
        NetworkStudyPanel.cpp \
        ScoreTableWidget.cpp \
        ServerWidget.cpp \
        StudentTreeWidget.cpp \
        main.cpp \
        widget.cpp

HEADERS += \
        CenterWindowTableView.h \
        ContentCell.h \
        CustomTreeItem.h \
        CustomTreeItemModel.h \
        CustomTreeItemStyleDelegate.h \
        CustomTreeView.h \
        LeftNaviListView.h \
        LeftNaviListWidgetDelegate.h \
        MyListWidget.h \
        MyUtil.h \
        MyWebImageView.h \
        NetworkStudyPanel.h \
        ScoreTableWidget.h \
        ServerWidget.h \
        StudentTreeWidget.h \
        singleton.h \
        widget.h

FORMS += \
        ContentCell.ui \
        CustomTreeView.ui \
        NetworkStudyPanel.ui \
        ServerWidget.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
