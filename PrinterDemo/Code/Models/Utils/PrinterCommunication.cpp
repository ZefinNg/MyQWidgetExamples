#include "PrinterCommunication.h"

#include <QDebug>

PrinterCommunication::PrinterCommunication(QObject *parent) : QObject(parent)
{
    m_devicePath = "/dev/ttymxc3";
    m_serialPort = new QextSerialPort(m_devicePath);
    m_gb2312     = QTextCodec::codecForName("GB2312");
    m_isRunning  = false;
    m_canSend    = true;

    m_dataQueue.clear();
    m_receivedData.clear();

    m_serialPort->setBaudRate(BAUD9600);
    m_serialPort->setDataBits(DATA_8);
    m_serialPort->setParity(PAR_NONE); //设置校验
    m_serialPort->setStopBits(STOP_1);
    m_serialPort->setFlowControl(FLOW_OFF); //设置流量控制
    m_serialPort->setTimeout(200);

    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(dataReceived()));
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

void PrinterCommunication::enqueueTransUnit(TransUnit transUnit)
{
    m_mutex.lock();
    m_dataQueue.enqueue(transUnit);
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

    qDebug() << "[Info]Printer communication thread starts.";
    while (m_isRunning) {
        if (!m_dataQueue.isEmpty()) {
            if (m_canSend) {
                m_mutex.lock();
                m_currentTransUnit = m_dataQueue.dequeue();
                m_mutex.unlock();
            }

            if (m_currentTransUnit.isQueryCmd()) {
                m_canSend = false;
            }

            qDebug() << __FUNCTION__ << __LINE__ << "size:" << m_currentTransUnit.byteArray().size();
            m_serialPort->write(m_currentTransUnit.byteArray().data(), m_currentTransUnit.byteArray().size());
        }
        else
            break;

        usleep(10 * 1000);
    }

    qDebug() << "[Info]Printer communication thread quit.";
}

void PrinterCommunication::dataReceived()
{
    if (m_serialPort->isReadable() && m_serialPort->bytesAvailable() > 0) {
        m_receivedData = m_serialPort->readAll();

        this->handleReceivedData(m_receivedData);
    }
}

void PrinterCommunication::handleReceivedData(QByteArray receivedData)
{

}
