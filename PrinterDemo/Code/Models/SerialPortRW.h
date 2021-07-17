#ifndef SERIALPORTRW_H
#define SERIALPORTRW_H

#include <QObject>
#include <QTextCodec>
#include "PrinterCmd.h"
#include "SerialPort/qextserialport.h"

class SerialPortRW : public QObject
{
    Q_OBJECT

public:
    SerialPortRW(QObject *parent = NULL);
    ~SerialPortRW();

    void setDevicePath(QString devicePath);

    bool open(QIODevice::OpenModeFlag mode = QIODevice::ReadWrite);
    void close();

    bool isOpen();

    bool initSerialPort();
    int writeData(QByteArray data);

signals:
    void receviedData(QString receviedData);

private slots:
    void onReceivedData();

private:
    QString m_portName;

    QextSerialPort *m_serialPort;
};

#endif // SERIALPORTRW_H
