#include "MainWidgetModel.h"
#include <QDebug>

MainWidgetModel::MainWidgetModel(QObject *parent) :
    QObject(parent)
{
    m_portName = "/dev/ttymxc3";
    m_serialPort = NULL;
    m_alignMode  = ALIGN_LEFT;
    m_gb2312 = QTextCodec::codecForName("GB2312");
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

MainWidgetModel::~MainWidgetModel()
{
    if (m_serialPort != NULL) {
        m_serialPort->deleteLater();
        m_serialPort = NULL;
    }
}

void MainWidgetModel::setDevicePath(QString devicePath)
{
    m_portName = devicePath;
    m_serialPort->setPortName(m_portName);
}

bool MainWidgetModel::openSerialPort(QIODevice::OpenModeFlag mode)
{
    return m_serialPort->open(mode);
}

void MainWidgetModel::closeSerialPort()
{
    m_serialPort->close();
}

bool MainWidgetModel::isSerialPortOpen()
{
    return m_serialPort->isOpen();
}

bool MainWidgetModel::initSerialPort()
{
    QString cmd = INIT_PRINTER;
    int writeResult = m_serialPort->write(cmd.toLatin1().data(), STRLEN(INIT_PRINTER));

    if (writeResult != cmd.size())
        return false;

    return true;
}

bool MainWidgetModel::printData(QString lineData, ALIGN_MODE alignMode)
{
    int length = this->calculateStringLength(lineData);

    int startPosition = 0;

    switch (alignMode) {
    case ALIGN_LEFT:
        break;
    case ALIGN_CENTER:
        startPosition = (LINE_TOTAL_LENGTH - length)/2;
        break;
    case ALIGN_RIGHT:
        startPosition = LINE_TOTAL_LENGTH - length;
        break;
    default:
        break;
    }

    this->setHorizontalTab(QList<int>() << startPosition);
    m_serialPort->write(EXEC_LEVEL_TABULATION, STRLEN(EXEC_LEVEL_TABULATION));
    m_serialPort->write(m_gb2312->fromUnicode(lineData).data());
    m_serialPort->write(CMD_ENTER, STRLEN(CMD_ENTER));
    m_serialPort->write(CMD_WRAP, STRLEN(CMD_WRAP));
    return true;
}

int MainWidgetModel::writeData2SerialPort(QByteArray data)
{
    m_serialPort->write(QUERY_PAPER_STATUS, STRLEN(QUERY_PAPER_STATUS));
//    m_serialPort->write(SET_ROTATION_ANGLE_180, STRLEN(SET_ROTATION_ANGLE_180));
    this->setRotationAngle(ANGLE_270);
//    m_serialPort->write(HORIZONTAL_ZOOM_4_TIMES, STRLEN(HORIZONTAL_ZOOM_4_TIMES));
//    m_serialPort->write(CMD_HIGHLIGHT_ON, STRLEN(CMD_HIGHLIGHT_ON));
    int writeResult = -1;
#if 1
    QString printData_62 = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString printData_32 = "1234567890abcdefghijklmnopqrstuvwxyzABCD";
    QString printData_16 = "白日依山尽，黄河入海流";
    QString gb2312Code = "\xC4\xE3\xBA\xC3";
//    qDebug() << "CMD_HTAB1 length:" << STRLEN(CMD_HTAB1);

//    this->setHorizontalMagnification(3);
//    this->setVerticalMagnification(3);
//    this->setHorizontalVerticalMagnification(3);
    m_serialPort->write(CMD_HTAB1, STRLEN(CMD_HTAB1));
    m_serialPort->write(EXEC_LEVEL_TABULATION, STRLEN(EXEC_LEVEL_TABULATION));
    writeResult = m_serialPort->write(m_gb2312->fromUnicode(printData_16).data());
//    writeResult = m_serialPort->write(m_gb2312.toLatin1().data());
    qDebug() << "Data writeResult:" << writeResult;
    m_serialPort->write(CMD_ENTER, STRLEN(CMD_ENTER));
    m_serialPort->write(CMD_WRAP, STRLEN(CMD_WRAP));

//    m_serialPort->write(HORIZONTAL_ZOOM_1_TIMES, STRLEN(HORIZONTAL_ZOOM_1_TIMES));
    this->setHorizontalMagnification(1);
    m_serialPort->write(CMD_HTAB1, STRLEN(CMD_HTAB1));
    m_serialPort->write(EXEC_LEVEL_TABULATION, STRLEN(EXEC_LEVEL_TABULATION));
    writeResult = m_serialPort->write(m_gb2312->fromUnicode(printData_32).data());
//    writeResult = m_serialPort->write(gb2312Code.toLatin1().data());
    qDebug() << "Data writeResult:" << writeResult;
    m_serialPort->write(CMD_ENTER, STRLEN(CMD_ENTER));
    m_serialPort->write(CMD_WRAP, STRLEN(CMD_WRAP));
#else
    QString title = "1234567890abcdefghijklmnopqrstuvwxyzABCD";
    QString author = "Su shi";
    m_serialPort->write(CMD_HTAB2, STRLEN(CMD_HTAB2));
    qDebug() << "sizeof(SET_ROTATION_ANGLE_270):" << sizeof(SET_ROTATION_ANGLE_270);
    qDebug() << "strlen(SET_ROTATION_ANGLE_270):" << strlen(SET_ROTATION_ANGLE_270);
    m_serialPort->write(EXEC_LEVEL_TABULATION, STRLEN(EXEC_LEVEL_TABULATION));
    writeResult = m_serialPort->write(m_gb2312->fromUnicode(title).data());
    m_serialPort->write(EXEC_LEVEL_TABULATION, STRLEN(EXEC_LEVEL_TABULATION));
    writeResult = m_serialPort->write(m_gb2312->fromUnicode(author).data());
    m_serialPort->write(CMD_ENTER, STRLEN(CMD_ENTER));
    m_serialPort->write(CMD_WRAP, STRLEN(CMD_WRAP));

#endif
    this->printBlankLine(2);
    return writeResult;
}

bool MainWidgetModel::setHorizontalMagnification(int times)
{
    if (times < 1 || times > 8) {
        qDebug() << "[Error]The horizontal magnification must be greater than or equal to 1 and less than or equal to 8.";
        return false;
    }

    QString tempCmd = "1B550";
    QString vaildCmdString = tempCmd + QString::number(times);
    QByteArray vaildCmd = QByteArray::fromHex(vaildCmdString.toLatin1());

    qDebug() << "VaildCmd size:" << vaildCmd.size();
    int writeLength = m_serialPort->write(vaildCmd.data(), vaildCmd.size());
    qDebug() << "WriteLength: " << writeLength;

    if (writeLength != vaildCmd.size())
        return false;

    return true;
}

bool MainWidgetModel::setVerticalMagnification(int times)
{
    if (times < 1 || times > 8) {
        qDebug() << "[Error]The vertical magnification must be greater than or equal to 1 and less than or equal to 8.";
        return false;
    }

    QString tempCmd = "1B560";
    QString vaildCmdString = tempCmd + QString::number(times);
    QByteArray vaildCmd = QByteArray::fromHex(vaildCmdString.toLatin1());

    qDebug() << "VaildCmd size:" << vaildCmd.size();
    int writeLength = m_serialPort->write(vaildCmd.data(), vaildCmd.size());

    if (writeLength != vaildCmd.size())
        return false;

    return true;
}

bool MainWidgetModel::setHorizontalVerticalMagnification(int times)
{
    if (times < 1 || times > 8) {
        qDebug() << "[Error]The horizontal & vertical magnification must be greater than or equal to 1 and less than or equal to 8.";
        return false;
    }

    QString tempCmd = "1B570";
    QString vaildCmdString = tempCmd + QString::number(times);
    QByteArray vaildCmd = QByteArray::fromHex(vaildCmdString.toLatin1());

    qDebug() << "VaildCmd size:" << vaildCmd.size();
    int writeLength = m_serialPort->write(vaildCmd.data(), vaildCmd.size());

    if (writeLength != vaildCmd.size())
        return false;

    return true;
}

bool MainWidgetModel::setRotationAngle(ROTATION_ANGLE angle)
{
    QString cmd = "1c490";

    switch (angle) {
    case ANGLE_0:   cmd += "0"; break;
    case ANGLE_90:  cmd += "1"; break;
    case ANGLE_180: cmd += "2"; break;
    case ANGLE_270: cmd += "3"; break;
    default:        cmd += "0"; break;
    }

    QByteArray vaildCmd = QByteArray::fromHex(cmd.toLatin1());
    int writeLength = m_serialPort->write(vaildCmd, vaildCmd.size());

    if (writeLength != vaildCmd.size())
        return false;

    return true;
}

MainWidgetModel::ALIGN_MODE MainWidgetModel::getAlignMode()
{
    return m_alignMode;
}

void MainWidgetModel::setAlignMode(ALIGN_MODE alignMode)
{
    m_alignMode = alignMode;
}

bool MainWidgetModel::setHorizontalTab(QList<int> tabList)
{
    if (tabList.count() > 4)
        return false;

    QString horiziontalTabTempCmd = "1B44";
    QString tabPosition = "";
    foreach (int tabValue, tabList) {
        tabPosition = QString("%1").arg(QString::number(tabValue, 16), 2, '0');
        horiziontalTabTempCmd += tabPosition;
    }
    horiziontalTabTempCmd += "00";

    QByteArray hexCmd = QByteArray::fromHex(horiziontalTabTempCmd.toLatin1());
    int writeLength = m_serialPort->write(hexCmd, hexCmd.size());

    if (writeLength != hexCmd.size())
        return false;

    return true;
}

bool MainWidgetModel::setAntiWhite(bool onOff)
{
    int writeLength = 0;
    if (onOff)
        writeLength = m_serialPort->write(CMD_ANTI_WHITE_ON, STRLEN(CMD_ANTI_WHITE_ON));
    else
        writeLength = m_serialPort->write(CMD_ANTI_WHITE_OFF, STRLEN(CMD_ANTI_WHITE_OFF));

    if (writeLength == STRLEN(CMD_ANTI_WHITE_ON))
        return true;

    return false;
}

void MainWidgetModel::onReceivedData()
{
    QByteArray readBuffer;
    if (m_serialPort->bytesAvailable() > 0) {
        readBuffer = m_serialPort->readAll();
//        emit receviedData(QString(readBuffer));
        qDebug() << "[Info]Serial port recevice:" << readBuffer.toHex();
    }

    return;
}

void MainWidgetModel::printBlankLine(int lines)
{
    for (int i = 0; i < lines; i++)
        m_serialPort->write(CMD_WRAP, STRLEN(CMD_WRAP));
}

int MainWidgetModel::calculateStringLength(QString text)
{
    int length = 0;
    for (int i = 0; i < text.size(); i++) {
        if (this->isChineseChar(text.at(i)))
            length += 2;
        else
            length +=1;
    }

    qDebug() << "Text length:" << length;
    return length;
}

bool MainWidgetModel::isChineseChar(QChar character)
{
    ushort unicodeValue = character.unicode();
    if (unicodeValue >= 0x4E00 && unicodeValue <= 0x9FA5)
        return true;

    return false;
}
