#include "MainWidgetController.h"

MainWidgetController::MainWidgetController(QObject *parent) :
    QObject(parent)
{
    m_mainWidgetModel = new MainWidgetModel(this);
}

MainWidgetController::~MainWidgetController()
{

}

bool MainWidgetController::openSerialPort(QIODevice::OpenModeFlag mode, QString devicePath)
{
    m_mainWidgetModel->setDevicePath(devicePath);
    return m_mainWidgetModel->openSerialPort(mode);
}

void MainWidgetController::closeSerialPort()
{
    m_mainWidgetModel->closeSerialPort();
}

void MainWidgetController::initSerialPort()
{
    m_mainWidgetModel->initSerialPort();
}

int MainWidgetController::writeData2SerialPort(QString printerData)
{
//    return m_mainWidgetModel->writeData2SerialPort(printerData.toLatin1());
    return true;
}

bool MainWidgetController::setHorizontalMagnification(int times)
{
//    return m_mainWidgetModel->setHorizontalMagnification(times);
    return true;
}

bool MainWidgetController::setVerticalMagnification(int times)
{
//    return m_mainWidgetModel->setVerticalMagnification(times);
    return true;
}

bool MainWidgetController::setHorizontalVerticalMagnification(int times)
{
//    return m_mainWidgetModel->setHorizontalVerticalMagnification(times);
    return true;
}

bool MainWidgetController::setRotationAngle(MainWidgetModel::ROTATION_ANGLE angle)
{
//    return m_mainWidgetModel->setRotationAngle(angle);
    return true;
}

bool MainWidgetController::setAntiWhite(bool onOff)
{
//    return m_mainWidgetModel->setAntiWhite(onOff);
    return true;
}

void MainWidgetController::printData(QString lineData, MainWidgetModel::ALIGN_MODE alignMode)
{
    m_mainWidgetModel->printData(lineData, alignMode);
}

void MainWidgetController::printBlankLine(int lines)
{
//    return m_mainWidgetModel->printBlankLine(lines);
}
