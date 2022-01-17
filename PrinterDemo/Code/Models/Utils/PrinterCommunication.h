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

    void appendTransUnit(TransUnit transUnit);

    qint64 write(const QByteArray &data);
    qint64 write(const char *data, qint64 len);

signals:
    void finishWork();

public slots:
    void doWork();
    void quitWork();

private slots:
    void dataReceived();

private:
    bool sendTransUnit(TransUnit &transUnit);
    void prependTransUnit(TransUnit transUnit);
    bool handleReceivedData(QByteArray receivedData, TransUnit::UNIT_QUERY_TYPE type);

private:
    QString         m_devicePath;
    QextSerialPort *m_serialPort;
    QTextCodec     *m_gb2312;
    QMutex          m_mutex;

    bool m_isRunning;
    bool m_isWaitingReply;

    QList<TransUnit>  m_dataList;
    QByteArray        m_receivedData;

    QTimer m_readTimer;
};

#endif // PRINTERCOMMUNICATION_H
