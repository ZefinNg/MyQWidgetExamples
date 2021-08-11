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
    Models/Utils/SerialPort/qextserialport.cpp \
    Models/Utils/SerialPort/posix_qextserialport.cpp \
    Models/Utils/SerialPort/qextserialbase.cpp \
    Models/Utils/SerialPort/qextserialport_unix.cpp \
    Models/MainWidgetModel.cpp \
    Controllers/MainWidgetController.cpp \
    Models/Utils/PrinterCommunication.cpp \
    Models/Domains/TransUnit.cpp

HEADERS  += Views/MainWidget.h \
    Models/Utils/SerialPort/qextserialport.h \
    Models/Utils/SerialPort/posix_qextserialport.h \
    Models/Utils/SerialPort/qextserialbase.h \
    Models/Utils/SerialPort/qextserialport_global.h \
    Models/Utils/SerialPort/qextserialport_p.h \
    Models/MainWidgetModel.h \
    Models/PrinterCmd.h \
    Controllers/MainWidgetController.h \
    Models/Utils/PrinterCommunication.h \
    Models/Domains/TransUnit.h

FORMS    += Views/MainWidget.ui

contains(DEFINES, ENABLE_ARM) {
    LIBS += -L/etc/tslib-install/lib -lts
}

RESOURCES += \
    Views/Resource/resource.qrc
