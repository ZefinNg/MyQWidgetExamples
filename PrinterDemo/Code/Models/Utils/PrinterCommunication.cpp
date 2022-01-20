#include "PrinterCommunication.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

#define RW_TIMEOUT_MS (2000)
#define SOFT_FLOW_CONTROL_XOFF (0x13)
#define SOFT_FLOW_CONTROL_XON  (0x11)
#define NORMAL_STATUS          (0x12)

PrinterCommunication::PrinterCommunication(QObject *parent) : QObject(parent)
{
    m_devicePath       = "/dev/ttymxc3";
    m_serialPort       = new QextSerialPort(m_devicePath);
    m_gb2312           = QTextCodec::codecForName("GB2312");
    m_isRunning        = false;
    m_isWaitingReply   = false;

    m_dataList.clear();
    m_receivedData.clear();

    m_serialPort->setBaudRate(BAUD9600);
    m_serialPort->setDataBits(DATA_8);
    m_serialPort->setParity(PAR_NONE); //设置校验
    m_serialPort->setStopBits(STOP_1);
    m_serialPort->setFlowControl(FLOW_OFF); //设置流量控制
    m_serialPort->setTimeout(200);

//    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(dataReceived()), Qt::QueuedConnection);
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
    QEventLoop readLoop;
    QTimer readTimer;
    readTimer.setSingleShot(true);

    connect(&readTimer, SIGNAL(timeout()), &readLoop, SLOT(quit()));
    connect(m_serialPort, SIGNAL(readyRead()), &readLoop, SLOT(quit()));
//    connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    m_isRunning = true;

    printf("[Info]Printer communication thread starts.\n");
    while (m_isRunning) {
        TransUnit tempTranUnit;

        //判断当前是否需要读取数据，不用则进入发送状态
        if (!m_isWaitingReply) {
            if (!m_dataList.isEmpty()) {
#if 1
                m_mutex.lock();
                tempTranUnit = m_dataList.takeFirst();
                m_mutex.unlock();

                if (tempTranUnit.resendTimes() > 0) {
                    if (!this->sendTransUnit(tempTranUnit)) {
                        if (tempTranUnit.resendTimes() > 0) {
                            this->prependTransUnit(tempTranUnit);
                            continue;
                        }
                    }
                }
                else
                    continue;

                if (tempTranUnit.isQueryCmd()) {
                    m_isWaitingReply = true;
                    continue;
                }
#endif
            }
            else {
//                m_isRunning = false;
//                emit finishWork();
//                break;
                m_isWaitingReply = true;
            }
        }
        else {//读取串口
//            this->readPrinter();
            readTimer.start(RW_TIMEOUT_MS);
            readLoop.exec();

            //等待打印机回复，判断状态
            if (m_serialPort->isReadable() && m_serialPort->bytesAvailable() > 0) {
                m_receivedData = m_serialPort->readAll();
                m_serialPort->flush();

                if (m_receivedData.size() > 0) {
                    m_isWaitingReply = !this->handleReceivedData(m_receivedData, tempTranUnit.unitType());
                    m_receivedData.clear();
                }
            }
            else {
                //若重发次数不为0，则准备重发
                if (tempTranUnit.resendTimes() > 0
                        && tempTranUnit.unitType() != TransUnit::NONE_TYPE) {
                    qDebug() << "[Info]Received data timeout. Ready to resend.";
                    this->prependTransUnit(tempTranUnit);
                    m_isWaitingReply = false;
                }
            }
        }
    }

    printf("[Info]Printer communication thread quit.\n");
}

void PrinterCommunication::quitWork()
{
    m_isRunning = false;
    printf("%s %d\n", __FUNCTION__, __LINE__);
}

void PrinterCommunication::dataReceived()
{
    if (m_serialPort->isReadable() && m_serialPort->bytesAvailable() > 0) {
        m_receivedData = m_serialPort->readAll().toHex();

        qDebug() << "[Info]Received data:" << m_receivedData;
//        this->handleReceivedData(m_receivedData);

        if (!m_isWaitingReply)
            m_isWaitingReply = false;
    }
}

bool PrinterCommunication::sendTransUnit(TransUnit& transUnit)
{
    QByteArray encodeData = "";
    int writeResult = -1;
    int dataLength  = 0;

    //重发次数-1
    transUnit.setResendTimes(transUnit.resendTimes()-1);

    if (transUnit.unitType() == TransUnit::PRINT_TEXT) {
        qDebug() << "[Info]Send data:" << QString::fromLocal8Bit(transUnit.byteArray());
        encodeData = m_gb2312->fromUnicode(QString(transUnit.byteArray()));
        qDebug() << "Tx:" << encodeData;
        dataLength = encodeData.count();
        writeResult = m_serialPort->write(encodeData.data());
    }
    else {
        qDebug() << "[Info]Send data type:" << transUnit.unitType();
        dataLength = transUnit.byteArray().size();
        writeResult = m_serialPort->write(transUnit.byteArray().data(), transUnit.byteArray().size());
    }

    if (writeResult != dataLength) {
        qDebug() << "WriteResult:" << writeResult << "dataLength:" << dataLength;
        qDebug() << "[Trace]Write error, prepend transUnit to resend.";
        return false;
    }

    return true;
}

void PrinterCommunication::prependTransUnit(TransUnit transUnit)
{
    m_mutex.lock();
    m_dataList.prepend(transUnit);
    m_mutex.unlock();
}

bool PrinterCommunication::handleReceivedData(QByteArray receivedData, TransUnit::UNIT_QUERY_TYPE type)
{
    qDebug() << "[Info]Rx:" << receivedData.toHex();
    qDebug() << "Rx size:"  << receivedData.size();

    int eachReply = 0;
    bool result = false;

    for (int i = 0; i < receivedData.size(); i++) {
        eachReply = receivedData[i];

        if (eachReply == SOFT_FLOW_CONTROL_XOFF)
            result = false;
        else if (eachReply == SOFT_FLOW_CONTROL_XON)
            result = true;
        else if (eachReply == NORMAL_STATUS)
            result = true;
        else {
            switch (type) {
            case TransUnit::NONE_TYPE:
                break;
            case TransUnit::QUERY_STATUS:
                break;
            case TransUnit::QUERY_OFFLINE:
                break;
            case TransUnit::QUERY_ERROR:
                break;
            case TransUnit::QUERY_PAPER:
                break;
            default:
                break;
            }
        }
    }

    return result;

    //判断收到的是否为XOFF、XON信号
//    qDebug() << "recvData:" << *recvData;
}
