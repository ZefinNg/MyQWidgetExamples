#ifndef MAINWIDGETMODEL_H
#define MAINWIDGETMODEL_H

#include <QObject>
#include <QTextCodec>
#include <QStringList>
#include <QImage>
#include <QThread>

#include "PrinterCmd.h"
#include "Utils/PrinterCommunication.h"

class MainWidgetModel : public QObject
{
    Q_OBJECT
public:
    enum ROTATION_ANGLE {
        ANGLE_0,
        ANGLE_90,
        ANGLE_180,
        ANGLE_270
    };

    enum ALIGN_MODE {
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };

    explicit MainWidgetModel(QObject *parent = 0);
    ~MainWidgetModel();

    void setDevicePath(QString devicePath);

    bool openSerialPort(QIODevice::OpenModeFlag mode = QIODevice::ReadWrite);
    void closeSerialPort();

    bool isSerialPortOpen();

    void initSerialPort();

    void printData(QString lineData, ALIGN_MODE alignMode);
    void printPicture(const QString filePath);

    //For debug
    void printData(QByteArray message);

#if 0
    int writeData2SerialPort(QByteArray data);
#endif

    bool setHorizontalMagnification(int times);
    bool setVerticalMagnification(int times);
    bool setHorizontalVerticalMagnification(int times);

    void setRotationAngle(enum ROTATION_ANGLE angle);

    MainWidgetModel::ALIGN_MODE getAlignMode();
    void setAlignMode(enum ALIGN_MODE alignMode);

    bool setHorizontalTab(QList<int> tabList);

    void setAntiWhite(bool onOff);

    void printBlankLine(int lines);

    void setLineSpace(const int lineSpacing);

signals:
    void receviedData(QString receviedData);

private slots:
//    void onReceivedData();
    void quitThread();

private:
    void queryPrinterStatus();

    int calculateStringLength(QString text);
    bool isChineseChar(QChar character);

    QByteArray makePrintPicPackage(const QList<int> dotList);
    void printPicData(const QList<int> dotList);

    QImage toGrayImage(QImage srcImage);

private:
    QThread *m_printThread;
    PrinterCommunication *m_printerCommunicaiton;
    enum ALIGN_MODE m_alignMode;
};

#endif // MAINWIDGETMODEL_H
