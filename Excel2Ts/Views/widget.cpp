#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      m_tsFixUp(new TsFixUp(this)),
      m_tsFilePath()
{
    ui->setupUi(this);

    connect(ui->btnSelectExcel,    SIGNAL(clicked()), this, SLOT(onBtnSelectExcelClicked()));
    connect(ui->btnSelectTs,       SIGNAL(clicked()), this, SLOT(onBtnSelectTsFileClicked()));
    connect(ui->btnStartConvert,   SIGNAL(clicked()), this, SLOT(onBtnStartConvertClicked()));
    connect(ui->btnOpenOutputDir,  SIGNAL(clicked()), this, SLOT(onBtnOpenOutputClicked()));
//    connect(ui->btnClose,        SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));
//    connect(ui->btnSetTitle,     SIGNAL(clicked()), this, SLOT(onBtnSetTitleClicked()));
//    connect(ui->btnSetSheetName, SIGNAL(clicked()), this, SLOT(onBtnSetSheetNameClicked()));
//    connect(ui->btnAddSheet,     SIGNAL(clicked()), this, SLOT(onBtnAddSheetClicked()));
//    connect(ui->btnDeleteSheet,  SIGNAL(clicked()), this, SLOT(onBtnDeleteSheetClicked()));
//    connect(ui->btnAddCell,      SIGNAL(clicked()), this, SLOT(onBtnAddCell()));

    ui->labelFormat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->labelFormat->setWordWrap(true);

    ui->lineEditExcelFile->setEnabled(false);
    ui->lineEditTsFile->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnSelectExcelClicked()
{
    QString excelFilePath = QFileDialog::getOpenFileName(this, "选择Excel文件", "C:\\", "Excel (*.xlsx *xls)");

    if (excelFilePath.isEmpty())
        return;

    ExcelHandler::HANDLE_ERROR result = m_tsFixUp->setExcelFile(excelFilePath);

    QString tips = "";

    switch (result) {
    case ExcelHandler::NORMAL:
        ui->lineEditExcelFile->setText(excelFilePath);
        return;
    case ExcelHandler::OPEN_FILE_FAILED:
        tips = "文件打开失败。";
        break;
    case ExcelHandler::FORMAT_ERROR:
        tips = "文件格式错误。";
        break;
    case ExcelHandler::REPEAT_KEY:
        tips = "文件存在重复的源文。";
        break;
    default:
        break;
    }

    //TODO：此处调用会导致段错误，待查
//    m_tsFixUp->closeExcelFile();
    QMessageBox::critical(this, "错误", tips);
}

void Widget::onBtnSelectTsFileClicked()
{
    m_tsFilePath = QFileDialog::getOpenFileName(this, "选择Ts文件", "C:\\", "Ts (*.ts *.xml)");

    if (m_tsFilePath.isEmpty())
        return;

    QFileInfo fileInfo(m_tsFilePath);

    m_outputPath = fileInfo.absoluteDir().path();
#ifdef WIN32
    m_outputPath.replace("/", "\\");
#else

#endif
    QString fileBaseName = fileInfo.baseName();
    QString curDateTime  = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    m_tsFixUp->setOutputTsFile(m_outputPath + fileBaseName + "_" + curDateTime + ".ts");
    m_tsFixUp->setTsFile(m_tsFilePath);

    ui->lineEditTsFile->setText(m_tsFilePath);
}

void Widget::onBtnStartConvertClicked()
{
    if (!m_tsFixUp->fixUpTsFile())
        QMessageBox::critical(this, "错误", "Ts文件完善失败!");
    else
        QMessageBox::information(this, "提示", "转换完成");
}

void Widget::onBtnOpenOutputClicked()
{
    if (m_tsFilePath.isEmpty())
        QMessageBox::critical(this, "错误", "未选择Ts文件!");
    else {
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_outputPath));
    }
}

void Widget::onExcelHandlerError(ExcelHandler::HANDLE_ERROR errorNum)
{
    switch (errorNum) {
    case ExcelHandler::OPEN_FILE_FAILED:
        QMessageBox::critical(this, "Error", "Open file failed.");
        break;
    case ExcelHandler::FORMAT_ERROR:
        QMessageBox::critical(this, "Error", "Excel file's text format is error.");
        break;
    case ExcelHandler::REPEAT_KEY:
        QMessageBox::critical(this, "Error", "There are duplicate key values.");
        break;
    default:
        break;
    }
}
#if 0
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
