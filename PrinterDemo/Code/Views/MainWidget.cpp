#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QDebug>
#include <QListView>

#pragma execution_character_set("utf-8")

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    m_readyPrintDataList.clear();
    m_mainWidgetController = new MainWidgetController(this);
    m_printTimer.setInterval(800);

    //设置背景图
//    QPalette mainWidgetPalette;
//    QPixmap backgroundPixmap(":/images/background.png");
//    mainWidgetPalette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
//    this->setPalette(mainWidgetPalette);

    //设置QTextBrowser为半透明
    ui->textBrowser->setStyleSheet("QTextBrowser{background-color:rgb(240, 240, 240, 125)};");
    //设置贴图后控件不会出现虚线框
    QString qssFocus = "QWidget:focus{outline: none;}";

    //设置打印按钮贴图
    QString qssButton = "QPushButton{border-image:url(:/images/button_release.png);}"\
                        "QPushButton:Pressed{border-image:url(:/images/button_press.png)}";

    //设置下拉框的箭头贴图
    QString qssDropDown = "QComboBox::drop-down {"\
                          "image:url(:/images/drop_down.png);"\
                          "width: 40px;}"\
                          "QComboBox QAbstractItemView::item{height:40px;}"\
                          "QComboBox{font-size:20pt;}";

    this->setStyleSheet(qssFocus + qssButton + qssDropDown);

    //设置开关按钮贴图
    ui->switchButton->setStyleSheet("QPushButton{border-image: url(:/images/switch_off.png);}");

    //设置下拉框的选项高度
    ui->horizontalMagnificationComboBox->setView(new QListView());
    ui->verticalMagnificationComboBox->setView(new QListView());
    ui->rotationAngleCombox->setView(new QListView());

    //设置按钮可正常出发clicked(bool)信号
    ui->switchButton->setCheckable(true);

    connect(ui->switchButton,           SIGNAL(clicked(bool)), this, SLOT(onSwtichButtonClicked(bool)));
    connect(ui->printOathButton,        SIGNAL(clicked()),     this, SLOT(onPrintOathButtonClicked()));
    connect(ui->printData2Button,       SIGNAL(clicked()),     this, SLOT(onPrintData2ButtonClicked()));
    connect(ui->printCopywritingButton, SIGNAL(clicked()),     this, SLOT(onPrintCopyWritingButtonClicked()));
    connect(ui->printGermanButton,      SIGNAL(clicked()),     this, SLOT(onPrintGermanButtonClicked()));
    connect(ui->printPic1Button,        SIGNAL(clicked()),     this, SLOT(onPirntPic1ButtonClicked()));

    connect(&m_printTimer, SIGNAL(timeout()), this, SLOT(onPrintTimerTimeout()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::onSwtichButtonClicked(bool isChecked)
{
    if (isChecked) {
#ifdef __arm__
        if (m_mainWidgetController->openSerialPort(QIODevice::ReadWrite, "/dev/ttymxc1")) {
#else
        if (m_mainWidgetController->openSerialPort(QIODevice::ReadWrite, "/dev/ttyS0")) {
#endif
            ui->textBrowser->append("[Info]Opening printer serial port successfully.");
            ui->switchButton->setStyleSheet("QPushButton{border-image: url(:/images/switch_on.png);}");
        }
        else
            ui->textBrowser->append("[Error]Opening printer serial port failed.");
    }
    else {
        m_mainWidgetController->closeSerialPort();

        ui->textBrowser->append("[Info]Close printer serial port.");
        ui->switchButton->setStyleSheet("QPushButton{border-image: url(:/images/switch_off.png);}");
    }
}

void MainWidget::onPrintOathButtonClicked()
{
    if (m_printTimer.isActive()) {
        ui->textBrowser->append("当前正在打印，请稍等……");
        return;
    }

    this->fillOathData();
    this->checkPrintCondition();
    ui->textBrowser->append("守夜人誓言打印中……");
//    m_printTimer.start();
    foreach (QString each, m_readyPrintDataList)
        m_mainWidgetController->printData(each);
}

void MainWidget::onPrintData2ButtonClicked()
{
    m_mainWidgetController->setRotationAngle(MainWidgetModel::ANGLE_180);
    m_mainWidgetController->printData("登鹳雀楼", MainWidgetModel::ALIGN_CENTER);
    m_mainWidgetController->printData("[作者] 王之涣", MainWidgetModel::ALIGN_CENTER);
    m_mainWidgetController->printData("白日依山尽，黄河入海流。", MainWidgetModel::ALIGN_LEFT);
    m_mainWidgetController->printData("欲穷千里目，更上一层楼。", MainWidgetModel::ALIGN_RIGHT);
    m_mainWidgetController->printBlankLine(1);
}

void MainWidget::onPrintCopyWritingButtonClicked()
{
    this->filleCopywritingData();
    this->checkPrintCondition();
    m_printTimer.start();
}

void MainWidget::onPrintGermanButtonClicked()
{
    m_mainWidgetController->printData("Γειά σου Κόσμε", MainWidgetModel::ALIGN_LEFT);
    m_mainWidgetController->printBlankLine(1);
    m_mainWidgetController->printBlankLine(1);
}

void MainWidget::onPirntPic1ButtonClicked()
{
#if 0
//    QByteArray message = "1B4B0F007C4444FF44447C00416254C8546241";
    m_mainWidgetController->setLineSpacing(0);
    QByteArray message = "1B4B4F01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
    m_mainWidgetController->printData(QByteArray::fromHex(message));
    m_mainWidgetController->printData(QByteArray::fromHex(message));
    m_mainWidgetController->printData(QByteArray::fromHex(message));
    m_mainWidgetController->printData(QByteArray::fromHex(message));
#else
    QString filePath = QFileDialog::getOpenFileName(this, "选择一张图片", "/", "Pic (*.png *.jpg *jpeg)");

    QImage image(filePath);
    if (image.isNull())
        ui->textBrowser->append("图片内容有误，请检查该图片是否存在");
    else if (image.width() > PIC_MAX_WIDTH)
        ui->textBrowser->append("图片宽度超出限制，请重新选择");
    else
        m_mainWidgetController->printPicture(filePath);
#endif
}

void MainWidget::onPrintTimerTimeout()
{
    if (!m_readyPrintDataList.isEmpty()) {
        QString readyPrintData = m_readyPrintDataList.takeFirst();
        m_mainWidgetController->printData(readyPrintData);
        m_mainWidgetController->printBlankLine(1);

        ui->textBrowser->append(readyPrintData);
    }
    else {
        m_printTimer.stop();
        m_mainWidgetController->printBlankLine(1);

        ui->textBrowser->append("----------------------------");
    }
}

void MainWidget::fillOathData()
{
    m_readyPrintDataList.clear();
    m_readyPrintDataList.append("长夜将至，我从今开始守望，至死方休。");
    m_readyPrintDataList.append("我将不娶妻，不封地，不生子。");
    m_readyPrintDataList.append("我将不戴王冠，不争荣宠。");
    m_readyPrintDataList.append("我将尽忠职守，生死于斯。");
    m_readyPrintDataList.append("我是黑暗中的利剑，");
    m_readyPrintDataList.append("长城上的守卫，");
    m_readyPrintDataList.append("抵御寒冷的烈焰，");
    m_readyPrintDataList.append("破晓时分的光线，");
    m_readyPrintDataList.append("唤醒眠者的号角，");
    m_readyPrintDataList.append("守护王国的坚盾。");
    m_readyPrintDataList.append("我将生命与荣耀献给守夜人，");
    m_readyPrintDataList.append("今夜如此，夜夜皆然。");
}

void MainWidget::filleCopywritingData()
{
    m_readyPrintDataList.clear();
    m_readyPrintDataList.append(QString::fromUtf8("后来啊，一个清晨"));
    m_readyPrintDataList.append(QString::fromUtf8("大雾散尽，不止清晨，不止大雾"));
    m_readyPrintDataList.append(QString::fromUtf8("大雾四起，我在无人处爱你"));
    m_readyPrintDataList.append(QString::fromUtf8("大雾散尽，人尽皆知"));
    m_readyPrintDataList.append(QString::fromUtf8("我爱你"));
}

void MainWidget::checkPrintCondition()
{
    this->configHorizontalMagnification();
    this->configVerticalMagnification();
    this->configRotationAngle();
    this->configAntiWhite();
}

bool MainWidget::configHorizontalMagnification()
{
    return m_mainWidgetController->setHorizontalMagnification(ui->horizontalMagnificationComboBox->currentIndex()+1);
}

bool MainWidget::configVerticalMagnification()
{
    return m_mainWidgetController->setVerticalMagnification(ui->verticalMagnificationComboBox->currentIndex()+1);
}

void MainWidget::configRotationAngle()
{
    m_mainWidgetController->setRotationAngle((MainWidgetModel::ROTATION_ANGLE)ui->rotationAngleCombox->currentIndex());
}

void MainWidget::configAntiWhite()
{
    m_mainWidgetController->setAntiWhite(ui->antiWhiteRadioButton->isChecked());
}
