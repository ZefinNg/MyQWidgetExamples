#ifndef MAINWIDGETMODEL_H
#define MAINWIDGETMODEL_H

#include <QObject>
#include <QTextCodec>
#include <QStringList>
#include "PrinterCmd.h"
#include "SerialPort/qextserialport.h"

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

    bool initSerialPort();
    bool printData(QString lineData, ALIGN_MODE alignMode);
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

signals:
    void receviedData(QString receviedData);

private slots:
    void onReceivedData();

private:
    int calculateStringLength(QString text);
    bool isChineseChar(QChar character);

private:
    QString        m_portName;
    QextSerialPort *m_serialPort;
    enum ALIGN_MODE m_alignMode;
    QTextCodec     *m_gb2312;
};

#endif // MAINWIDGETMODEL_H
