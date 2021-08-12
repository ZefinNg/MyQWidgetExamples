#include "MainWidgetModel.h"
#include <QDebug>

MainWidgetModel::MainWidgetModel(QObject *parent) :
    QObject(parent)
{
    m_alignMode  = ALIGN_LEFT;
    m_printerCommunicaiton = new PrinterCommunication();
    m_printThread = new QThread();
    m_printerCommunicaiton->moveToThread(m_printThread);

    connect(m_printThread, SIGNAL(started()),  m_printerCommunicaiton, SLOT(doWork()));
    connect(m_printerCommunicaiton, SIGNAL(finishWork()), this, SLOT(quitThread()));
}

MainWidgetModel::~MainWidgetModel()
{
    if (m_printerCommunicaiton != NULL) {
        m_printerCommunicaiton->deleteLater();
        m_printerCommunicaiton = NULL;
    }

    if (m_printThread != NULL) {
        m_printThread->quit();
        m_printThread->wait(500);
        m_printThread->deleteLater();
        m_printThread = NULL;
    }
}

void MainWidgetModel::setDevicePath(QString devicePath)
{
    m_printerCommunicaiton->setDevicePath(devicePath);
}

bool MainWidgetModel::openSerialPort(QIODevice::OpenModeFlag mode)
{
    if (m_printerCommunicaiton->openSerialPort(mode)) {
        this->initSerialPort();
        return true;
    }

    return false;
}

void MainWidgetModel::closeSerialPort()
{
    m_printerCommunicaiton->closeSerialPort();
}

bool MainWidgetModel::isSerialPortOpen()
{
    return m_printerCommunicaiton->isSerialPortOpen();
}

void MainWidgetModel::initSerialPort()
{
    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);
    transUnit.setByteArray(INIT_PRINTER);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();
}

void MainWidgetModel::queryPrinterStatus()
{
    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::QUERY_STATUS);
    transUnit.setByteArray(QUERY_TRANSPORT_DEVICE_STATUS);
    m_printerCommunicaiton->appendTransUnit(transUnit);

    transUnit.setUnitType(TransUnit::QUERY_OFFLINE);
    transUnit.setByteArray(QUERY_OFFLINE_STATUS);
    m_printerCommunicaiton->appendTransUnit(transUnit);

    transUnit.setUnitType(TransUnit::QUERY_ERROR);
    transUnit.setByteArray(QUERY_ERROR_STATUS);
    m_printerCommunicaiton->appendTransUnit(transUnit);

    transUnit.setUnitType(TransUnit::QUERY_PAPER);
    transUnit.setByteArray(QUERY_PAPER_STATUS);
    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();
}

void MainWidgetModel::printData(QString lineData, ALIGN_MODE alignMode)
{
#if 0
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
#else
    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::SNED_DATA);
    transUnit.setByteArray(lineData.toLatin1());
    m_printerCommunicaiton->appendTransUnit(transUnit);

    transUnit.setUnitType(TransUnit::PAPER_FEED);
    transUnit.setByteArray(CMD_ENTER);
    m_printerCommunicaiton->appendTransUnit(transUnit);

    transUnit.setUnitType(TransUnit::PAPER_FEED);
    transUnit.setByteArray(CMD_WRAP);
    m_printerCommunicaiton->appendTransUnit(transUnit);

    printf("%s %d Thread is running:%d\n", __FUNCTION__, __LINE__, m_printThread->isRunning());

    if (!m_printThread->isRunning() || m_printThread->isFinished()) {
        printf("Thread ready to start.\n");
        m_printThread->start();
    }
    printf("%s %d Thread is running:%d\n", __FUNCTION__, __LINE__, m_printThread->isRunning());

#endif
}

void MainWidgetModel::quitThread()
{
    m_printThread->quit();
    m_printThread->wait(500);
}

#if 0
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
#endif

bool MainWidgetModel::setHorizontalMagnification(int times)
{
    if (times < SCALE_MIN_TIMES || times > SCALE_MAX_TIMES) {
        qDebug() << "[Error]The horizontal magnification must be greater than or equal to 1 and less than or equal to 8.";
        return false;
    }

    QString tempCmd = "1B550";
    QString vaildCmdString = tempCmd + QString::number(times);
    QByteArray vaildCmd = QByteArray::fromHex(vaildCmdString.toLatin1());

    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);
    transUnit.setByteArray(vaildCmd);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();

    return true;
}

bool MainWidgetModel::setVerticalMagnification(int times)
{
    if (times < SCALE_MIN_TIMES || times > SCALE_MAX_TIMES) {
        qDebug() << "[Error]The vertical magnification must be greater than or equal to 1 and less than or equal to 8.";
        return false;
    }

    QString tempCmd = "1B560";
    QString vaildCmdString = tempCmd + QString::number(times);
    QByteArray vaildCmd = QByteArray::fromHex(vaildCmdString.toLatin1());

    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);
    transUnit.setByteArray(vaildCmd);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();

    return true;
}

bool MainWidgetModel::setHorizontalVerticalMagnification(int times)
{
    if (times < SCALE_MIN_TIMES || times > SCALE_MAX_TIMES) {
        qDebug() << "[Error]The horizontal & vertical magnification must be greater than or equal to 1 and less than or equal to 8.";
        return false;
    }

    QString tempCmd = "1B570";
    QString vaildCmdString = tempCmd + QString::number(times);
    QByteArray vaildCmd = QByteArray::fromHex(vaildCmdString.toLatin1());

    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);
    transUnit.setByteArray(vaildCmd);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();

    return true;
}

void MainWidgetModel::setRotationAngle(ROTATION_ANGLE angle)
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

    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);
    transUnit.setByteArray(vaildCmd);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();
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
    TransUnit transUnit;

    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);
    transUnit.setByteArray(hexCmd);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();

    return true;
}

void MainWidgetModel::setAntiWhite(bool onOff)
{
    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::CONFIG_FORMAT);

    if (onOff)
        transUnit.setByteArray(CMD_ANTI_WHITE_ON);
    else
        transUnit.setByteArray(CMD_ANTI_WHITE_OFF);

    m_printerCommunicaiton->appendTransUnit(transUnit);

    if (!m_printThread->isRunning())
        m_printThread->start();
}

void MainWidgetModel::printBlankLine(int lines)
{
    TransUnit transUnit;
    transUnit.setUnitType(TransUnit::PAPER_FEED);

    for (int i = 0; i < lines; i++) {
        transUnit.setByteArray(CMD_WRAP);
        m_printerCommunicaiton->appendTransUnit(transUnit);
    }

    if (!m_printThread->isRunning())
        m_printThread->start();
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
