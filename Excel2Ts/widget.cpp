#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnOpen,  SIGNAL(clicked()), this, SLOT(onBtnOpenClicked()));
    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));

    m_excelRW = new ExcelReadWrite(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnOpenClicked()
{
    if (!m_excelRW->openFile("C:\\Users\\zefeng.wu\\Desktop\\万孚 POCT 数据管理系统传输日志.xlsx"))
        QMessageBox::critical(this, "Error", "Open file failed.");
    else {
        qDebug() << m_excelRW->title();
        qDebug() << m_excelRW->getWorkSheetCount();
    }
}

void Widget::onBtnCloseClicked()
{
    m_excelRW->closeFile();
}
