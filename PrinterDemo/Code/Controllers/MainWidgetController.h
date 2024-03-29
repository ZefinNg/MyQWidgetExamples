#ifndef MAINWIDGETCONTROLLER_H
#define MAINWIDGETCONTROLLER_H

#include <QObject>
#include "../Models/MainWidgetModel.h"

class MainWidgetController : public QObject
{
    Q_OBJECT
public:
    explicit MainWidgetController(QObject *parent = 0);
    ~MainWidgetController();

    bool openSerialPort(QIODevice::OpenModeFlag mode, QString devicePath = "/dev/ttymxc3");
    void closeSerialPort();

    void initSerialPort();

    int writeData2SerialPort(QString printerData);

    bool setHorizontalMagnification(int times);
    bool setVerticalMagnification(int times);
    bool setHorizontalVerticalMagnification(int times);

    void setRotationAngle(MainWidgetModel::ROTATION_ANGLE angle);

    void setAntiWhite(bool onOff);

    void printData(QString lineData, MainWidgetModel::ALIGN_MODE alignMode = MainWidgetModel::ALIGN_CENTER);
    void printPicture(const QString filePath);

    void setLineSpacing(const int lineSpacing);

    //For debug
    void printData(QByteArray message);

    void printBlankLine(int lines);

signals:

public slots:

private:
    MainWidgetModel *m_mainWidgetModel;

};

#endif // MAINWIDGETCONTROLLER_H
