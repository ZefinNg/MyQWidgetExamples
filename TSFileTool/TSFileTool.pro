QT       += core gui xml

#For QtXlsx
QT       += xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

contains(QT, xlsx) {
    HEADERS += \
    Service/Utils/ExcelReadWriterQtXlsx/ExcelRW.h

    SOURCES += \
    Service/Utils/ExcelReadWriterQtXlsx/ExcelRW.cpp
}
#else {
#    #For AxObjcect
#    QT       += axcontainer

#    HEADERS += \
#        Service/Utils/ExcelReadWriterAxObject/ExcelReadWriter.h

#    SOURCES += \
#        Service/Utils/ExcelReadWriterAxObject/ExcelReadWriter.cpp
#}


INCLUDEPATH += Service/

SOURCES += \
    Service/ErrorTxtFixUp/ErrorTxtFixUp.cpp \
    Service/ExcelHandler/ExcelHandler.cpp \
    Service/SourceFileHandler/SourceFileHandler.cpp \
    Service/TsExcelHandler/TranslationBlock.cpp \
    Service/TsExcelHandler/TsExcelHandler.cpp \
    Service/TsFixUp/TsFixUp.cpp \
    Service/TxtExcelHandler/TxtExcelHandler.cpp \
    Views/Excel2ErrorFileWidget.cpp \
    Views/Excel2TsWidget.cpp \
    main.cpp \
    Views/widget.cpp

HEADERS += \
    Service/ErrorTxtFixUp/ErrorTxtFixUp.h \
    Service/ExcelHandler/ExcelHandler.h \
    Service/SourceFileHandler/SourceFileHandler.h \
    Service/TsExcelHandler/TranslationBlock.h \
    Service/TsExcelHandler/TsExcelHandler.h \
    Service/TsFixUp/TsFixUp.h \
    Service/TxtExcelHandler/TxtExcelHandler.h \
    Views/Excel2ErrorFileWidget.h \
    Views/Excel2TsWidget.h \
    Views/widget.h

FORMS += \
    Views/Excel2ErrorFileWidget.ui \
    Views/Excel2TsWidget.ui \
    Views/widget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Views/Images.qrc

RC_ICONS += ./Views/Resources/icon.ico
