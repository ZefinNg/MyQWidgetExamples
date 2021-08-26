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
        this->getExcelFileInfo();
    }
}

void Widget::onBtnCloseClicked()
{
    m_excelRW->closeFile();
}

void Widget::getExcelFileInfo()
{
    qDebug() << "Title:" << m_excelRW->title();
    int worksheetCount = m_excelRW->getWorksheetCount();
    qDebug() << "worksheet Count:" << worksheetCount;

    for (int i = 1; i <= worksheetCount; i++) {
        if (m_excelRW->setCurrentWorkSheet(i)) {
            qDebug() << "Worksheet Name:" << m_excelRW->getWorksheetName();
            qDebug() << "Rows:" << m_excelRW->getRows();
            qDebug() << "Columns:" << m_excelRW->getColumns();
            qDebug() << "Start rows:" << m_excelRW->getStartRows();
            qDebug() << "Start columns:" << m_excelRW->getStartColumns();
        }
    }
}
