#-------------------------------------------------
#
# Project created by QtCreator 2023-06-28T15:17:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeTracker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src/

SOURCES += \
    AppInfoJson.cpp \
    src/Common/Helper.cpp \
    src/DatabaseManager/DatabaseManager.cpp \
        main.cpp \
        MainWidget.cpp \
    ConfigManager.cpp \
    ApplicationInfo.cpp

HEADERS += \
    AppInfoJson.h \
    src/Common/Helper.h \
    src/DatabaseManager/DatabaseManager.h \
        MainWidget.h \
    ConfigManager.h \
    ApplicationInfo.h

RESOURCES += \
    res.qrc

win32 {
    RC_FILE = app.rc
}
