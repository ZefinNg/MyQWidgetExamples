#ifndef MAINWIDGETMODEL_H
#define MAINWIDGETMODEL_H

#include <QObject>
#include <QTextCodec>
#include <QStringList>
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
    bool printData(QString lineData, ALIGN_MODE alignMode);
#if 0
    int writeData2SerialPort(QByteArray data);

    bool setHorizontalMagnification(int times);
    bool setVerticalMagnification(int times);
    bool setHorizontalVerticalMagnification(int times);

    bool setRotationAngle(enum ROTATION_ANGLE angle);

    MainWidgetModel::ALIGN_MODE getAlignMode();
    void setAlignMode(enum ALIGN_MODE alignMode);

    bool setHorizontalTab(QList<int> tabList);

    bool setAntiWhite(bool onOff);

    void printBlankLine(int lines);
#endif

signals:
    void receviedData(QString receviedData);

private slots:
//    void onReceivedData();

private:
    void queryPrinterStatus();

    int calculateStringLength(QString text);
    bool isChineseChar(QChar character);

private:
    QThread *m_printThread;
    PrinterCommunication *m_printerCommunicaiton;
    enum ALIGN_MODE m_alignMode;
};

#endif // MAINWIDGETMODEL_H
