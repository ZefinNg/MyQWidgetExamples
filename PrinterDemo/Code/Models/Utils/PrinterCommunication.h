#ifndef PRINTERCOMMUNICATION_H
#define PRINTERCOMMUNICATION_H

#include <QObject>
#include <QTextCodec>
#include <QQueue>
#include <QMutex>
#include <QTimer>
#include <unistd.h>

#include "../PrinterCmd.h"
#include "SerialPort/qextserialport.h"
#include "../Domains/TransUnit.h"

class PrinterCommunication : public QObject
{
    Q_OBJECT
public:
    explicit PrinterCommunication(QObject *parent = 0);
    ~PrinterCommunication();

    void setDevicePath(QString devicePath);

    bool openSerialPort(QIODevice::OpenModeFlag mode = QIODevice::ReadWrite);
    void closeSerialPort();

    bool isSerialPortOpen();

    void enqueueTransUnit(TransUnit tarnsUnit);

    qint64 write(const QByteArray &data);
    qint64 write(const char *data, qint64 len);

signals:

public slots:
    void doWork();

private slots:
    void dataReceived();

private:
    void handleReceivedData(QByteArray receivedData);

private:
    QString         m_devicePath;
    QextSerialPort *m_serialPort;
    QTextCodec     *m_gb2312;
    QMutex          m_mutex;

    bool m_isRunning;
    bool m_canSend;

    QQueue<TransUnit> m_dataQueue;
    QByteArray        m_receivedData;
    TransUnit         m_currentTransUnit;

    QTimer m_readTimer;
};

#endif // PRINTERCOMMUNICATION_H
