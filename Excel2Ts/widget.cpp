#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnOpen,         SIGNAL(clicked()), this, SLOT(onBtnOpenClicked()));
    connect(ui->btnClose,        SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));
    connect(ui->btnSetTitle,     SIGNAL(clicked()), this, SLOT(onBtnSetTitleClicked()));
    connect(ui->btnSetSheetName, SIGNAL(clicked()), this, SLOT(onBtnSetSheetNameClicked()));
    connect(ui->btnAddSheet,     SIGNAL(clicked()), this, SLOT(onBtnAddSheetClicked()));
    connect(ui->btnDeleteSheet,  SIGNAL(clicked()), this, SLOT(onBtnDeleteSheetClicked()));
    connect(ui->btnAddCell,      SIGNAL(clicked()), this, SLOT(onBtnAddCell()));

//    m_excelRW = new ExcelReadWrite(this);
}

Widget::~Widget()
{
    delete ui;
}

#if 0
void Widget::onBtnOpenClicked()
{
    if (!m_excelRW->openFile("D:\\万孚 POCT 数据管理系统传输日志.xlsx"))
        QMessageBox::critical(this, "Error", "Open file failed.");
    else {
        this->getExcelFileInfo();
    }
}

void Widget::onBtnCloseClicked()
{
    m_excelRW->closeFile();
}

void Widget::onBtnSetTitleClicked()
{
    bool result = m_excelRW->setTitle(ui->lineEditTitle->text());
    qDebug() << "Set title:" << result;
    qDebug() << "New title:" << m_excelRW->getTitle();
}

void Widget::onBtnSetSheetNameClicked()
{
    qDebug() << "SheetName:" << m_excelRW->getWorksheetName();
    bool result = m_excelRW->setWorksheetName(ui->lineEditSheetName->text());
    qDebug() << "Set sheetName:" << result;
    qDebug() << "New sheetName:" << m_excelRW->getWorksheetName();
}

void Widget::onBtnAddSheetClicked()
{
    m_excelRW->appendWorksheet();
}

void Widget::onBtnDeleteSheetClicked()
{
    qDebug() << "Now sheet count:" << m_excelRW->getWorksheetCount();
    m_excelRW->deleteCurrentWorksheet();
    qDebug() << "Delete later, sheet count:" << m_excelRW->getWorksheetCount();
}

void Widget::onBtnAddCell()
{
    m_excelRW->setCellText("我是胖虎，Over.", 6, 1);
    m_excelRW->setCellText("我是路飞，我是要当海贼王的男人，Over.", 6, 2,
                           ExcelReadWrite::ALIGN_RIGHT,
                           ExcelReadWrite::ALIGN_BOTTOM,
                           true);
}

void Widget::getExcelFileInfo()
{
    qDebug() << "Title:" << m_excelRW->getTitle();
    int worksheetCount = m_excelRW->getWorksheetCount();
    qDebug() << "worksheet Count:" << worksheetCount;
    QStringList sheetList;

    for (int i = 1; i <= worksheetCount; i++) {
        if (m_excelRW->setCurrentWorkSheet(i)) {
            QString sheetName = m_excelRW->getWorksheetName();
            int rowCount = m_excelRW->getRows();
            int colCount = m_excelRW->getColumns();
            int startRow = m_excelRW->getStartRows();
            int startCol = m_excelRW->getStartColumns();

//            qDebug() << "Worksheet Name:" << sheetName;
//            qDebug() << "Rows:"    << rowCount;
//            qDebug() << "Columns:" << colCount;
//            qDebug() << "Start rows:"    << startRow;
//            qDebug() << "Start columns:" << startCol;

            sheetList.append(sheetName);
        }
    }

    m_excelRW->setCurrentWorkSheet(worksheetCount);
//    qDebug() << m_excelRW->getCellText(7, 4);

//    qDebug() << sheetList.indexOf("故障表");
}
#endif
