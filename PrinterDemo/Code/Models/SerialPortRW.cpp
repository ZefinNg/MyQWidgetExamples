#include "SerialPortRW.h"
#include <QDebug>

SerialPortRW::SerialPortRW(QObject *parent) :
    QObject(parent)
{
    m_portName = "/dev/ttymxc3";
    m_serialPort = NULL;

    m_serialPort = new QextSerialPort();
    m_serialPort->setPortName(m_portName);
    m_serialPort->setBaudRate(BAUD9600);
    m_serialPort->setDataBits(DATA_8);
    m_serialPort->setParity(PAR_NONE); //设置校验
    m_serialPort->setStopBits(STOP_1);
    m_serialPort->setFlowControl(FLOW_OFF); //设置流量控制
    m_serialPort->setTimeout(200);

    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(onReceivedData()));
}

SerialPortRW::~SerialPortRW()
{
    if (m_serialPort != NULL) {
        m_serialPort->deleteLater();
        m_serialPort = NULL;
    }
}

void SerialPortRW::setDevicePath(QString devicePath)
{
    m_portName = devicePath;
    m_serialPort->setPortName(m_portName);
}

bool SerialPortRW::open(QIODevice::OpenModeFlag mode)
{
    qDebug() << m_portName;

    return m_serialPort->open(mode);
}

void SerialPortRW::close()
{
    m_serialPort->close();
}

bool SerialPortRW::isOpen()
{
    return m_serialPort->isOpen();
}

bool SerialPortRW::initSerialPort()
{
    QString cmd = INIT_PRINTER;
    int writeResult = m_serialPort->write(cmd.toLatin1().data());

    if (writeResult != cmd.size())
        return false;

    return true;
}

int SerialPortRW::writeData(QByteArray data)
{
#if 0
    return m_serialPort->write(data.data());
#else
    if (!this->initSerialPort())
        return -1;

    int writeResult =  m_serialPort->write(QUERY_PAPER_STATUS);
    qDebug() << "WriteResult:" << writeResult;

    QTextCodec *gb2312 = QTextCodec::codecForName("GB2312");
    QString printData = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    m_serialPort->write("\x1B\x44\x01\x00");
    m_serialPort->write(EXEC_LEVEL_TABULATION);
    m_serialPort->write((gb2312->fromUnicode(printData).data()));
    m_serialPort->write(CMD_ENTER);
    m_serialPort->write(CMD_WRAP);

    return writeResult;
#endif
}

void SerialPortRW::onReceivedData()
{
    QByteArray readBuffer;
    if (m_serialPort->bytesAvailable() > 0) {
        readBuffer = m_serialPort->readAll();
//        emit receviedData(QString(readBuffer));
        qDebug() << "[Info]Serial port recevice:" << readBuffer.toHex();
    }

    return;
}
