#include "PrinterCommunication.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

PrinterCommunication::PrinterCommunication(QObject *parent) : QObject(parent)
{
    m_devicePath = "/dev/ttymxc3";
    m_serialPort = new QextSerialPort(m_devicePath);
    m_gb2312     = QTextCodec::codecForName("GB2312");
    m_isRunning  = false;
    m_canSend    = true;

    m_dataList.clear();
    m_receivedData.clear();

    m_serialPort->setBaudRate(BAUD9600);
    m_serialPort->setDataBits(DATA_8);
    m_serialPort->setParity(PAR_NONE); //设置校验
    m_serialPort->setStopBits(STOP_1);
    m_serialPort->setFlowControl(FLOW_OFF); //设置流量控制
    m_serialPort->setTimeout(200);

    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(dataReceived()), Qt::QueuedConnection);
}

PrinterCommunication::~PrinterCommunication()
{
    if (m_serialPort != NULL) {
        m_serialPort->close();
        m_serialPort->deleteLater();
        m_serialPort = NULL;
    }
}

void PrinterCommunication::setDevicePath(QString devicePath)
{
    m_devicePath = devicePath;
    m_serialPort->setPortName(m_devicePath);
}

bool PrinterCommunication::openSerialPort(QIODevice::OpenModeFlag mode)
{
    return m_serialPort->open(mode);
}

void PrinterCommunication::closeSerialPort()
{
    m_serialPort->close();
}

bool PrinterCommunication::isSerialPortOpen()
{
    return m_serialPort->isOpen();
}

void PrinterCommunication::appendTransUnit(TransUnit transUnit)
{
    m_mutex.lock();
    m_dataList.append(transUnit);
    m_mutex.unlock();
}

qint64 PrinterCommunication::write(const QByteArray &data)
{
    return m_serialPort->write(data);
}

qint64 PrinterCommunication::write(const char *data, qint64 len)
{
    return m_serialPort->write(data, len);
}

void PrinterCommunication::doWork()
{
    m_isRunning = true;
    int writeResult = -1;
    int dataLength  = 0;
    QByteArray encodeData = "";

//    qDebug() << "[Info]Printer communication thread starts.";
    printf("[Info]Printer communication thread starts.\n");
    while (m_isRunning) {
        qDebug() << __FUNCTION__ << __LINE__;
        if (!m_dataList.isEmpty()) {
            if (m_canSend) {
                qDebug() << __FUNCTION__ << __LINE__;
                m_mutex.lock();
                m_currentTransUnit = m_dataList.takeFirst();
                m_mutex.unlock();
                qDebug() << __FUNCTION__ << __LINE__;
            }
            else {
                qDebug() << __FUNCTION__ << __LINE__;
                this->prependTransUnit(m_currentTransUnit);
                m_canSend = true;
                continue;
            }

            if (m_currentTransUnit.isQueryCmd()) {
                qDebug() << __FUNCTION__ << __LINE__;
                m_canSend = false;
            }

#if 1
            if (m_currentTransUnit.unitType() == TransUnit::SNED_DATA) {
                qDebug() << "[Info]Send data:" << QString::fromLocal8Bit(m_currentTransUnit.byteArray());
                encodeData = m_gb2312->fromUnicode(QString(m_currentTransUnit.byteArray()));
                dataLength = encodeData.count();
                writeResult = m_serialPort->write(encodeData.data());
            }
            else {
                qDebug() << "[Info]Send data type:" << m_currentTransUnit.unitType();
                dataLength = m_currentTransUnit.byteArray().size();
                writeResult = m_serialPort->write(m_currentTransUnit.byteArray().data(), m_currentTransUnit.byteArray().size());
            }

            if (writeResult != dataLength) {
                qDebug() << "WriteResult:" << writeResult << "dataLength:" << dataLength;
                this->prependTransUnit(m_currentTransUnit);
                m_canSend = true;
                qDebug() << "[Trace]Write error, prepend transUnit to resend.";
            }
#endif
        }
        else {
            m_isRunning = false;
            emit finishWork();
            break;
        }

        usleep(10 * 1000);

        //能够正常获取到串口的数据
        QApplication::processEvents();
    }

//    qDebug() << "[Info]Printer communication thread quit.";
    printf("[Info]Printer communication thread quit.\n");
    return;
}

void PrinterCommunication::quitWork()
{
    m_isRunning = false;
    printf("%s %d\n", __FUNCTION__, __LINE__);
}

void PrinterCommunication::dataReceived()
{
//    if (m_serialPort->isReadable() && m_serialPort->bytesAvailable() > 0) {
        m_receivedData = m_serialPort->readAll().toHex();

        qDebug() << "[Info]Received data:" << m_receivedData;
        this->handleReceivedData(m_receivedData);
//    }

    m_canSend = true;
}

void PrinterCommunication::prependTransUnit(TransUnit transUnit)
{
    m_mutex.lock();
    m_dataList.prepend(transUnit);
    m_mutex.unlock();
}

void PrinterCommunication::handleReceivedData(QByteArray receivedData)
{

}
