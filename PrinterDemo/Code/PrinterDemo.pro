#-------------------------------------------------
#
# Project created by QtCreator 2021-07-01T11:20:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrinterDemo
TEMPLATE = app

#DEFINES += ENABLE_ARM

SOURCES += main.cpp\
    Views/MainWidget.cpp \
    Models/SerialPort/qextserialport.cpp \
    Models/SerialPort/posix_qextserialport.cpp \
    Models/SerialPort/qextserialbase.cpp \
    Models/SerialPort/qextserialport_unix.cpp \
    Controllers/MainWidgetController.cpp \
    Models/MainWidgetModel.cpp

HEADERS  += Views/MainWidget.h \
    Models/SerialPort/qextserialport.h \
    Models/SerialPort/posix_qextserialport.h \
    Models/SerialPort/qextserialbase.h \
    Models/SerialPort/qextserialport_global.h \
    Models/SerialPort/qextserialport_p.h \
    Controllers/MainWidgetController.h \
    Models/MainWidgetModel.h \
    Models/PrinterCmd.h

FORMS    += Views/MainWidget.ui

contains(DEFINES, ENABLE_ARM) {
    LIBS += -L/etc/tslib-install/lib -lts
}

RESOURCES += \
    Views/Resource/resource.qrc
