#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QListView>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      m_tsFixUp(new TsFixUp(this)),
      m_tsFilePath(),
      m_xlsxFilePath(),
      m_outputFilePath(),
      m_fileTips()
{
    ui->setupUi(this);

    connect(ui->btnSelectExcel,    SIGNAL(clicked()), this, SLOT(onBtnSelectExcelClicked()));
    connect(ui->btnSelectTs,       SIGNAL(clicked()), this, SLOT(onBtnSelectTsFileClicked()));

    connect(ui->btnExcel2Ts,       SIGNAL(clicked()), this, SLOT(onBtnExcel2TsClicked()));
    connect(ui->btnTs2Excel,       SIGNAL(clicked()), this, SLOT(onBtnTs2ExcelClicked()));
    connect(ui->btnOpenOutputDir,  SIGNAL(clicked()), this, SLOT(onBtnOpenOutputClicked()));
//    connect(ui->btnClose,        SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));
//    connect(ui->btnSetTitle,     SIGNAL(clicked()), this, SLOT(onBtnSetTitleClicked()));
//    connect(ui->btnSetSheetName, SIGNAL(clicked()), this, SLOT(onBtnSetSheetNameClicked()));
//    connect(ui->btnAddSheet,     SIGNAL(clicked()), this, SLOT(onBtnAddSheetClicked()));
//    connect(ui->btnDeleteSheet,  SIGNAL(clicked()), this, SLOT(onBtnDeleteSheetClicked()));
//    connect(ui->btnAddCell,      SIGNAL(clicked()), this, SLOT(onBtnAddCell()));

    this->setWindowTitle("TSFileTool");
    //与.pro中的RC_ICONS效果一样
//    this->setWindowIcon(QIcon(":/Resources/icon.ico"));
    this->setStyleSheet("#widget{border-image: url(:/Resources/background.png);}");

    ui->labelFormat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->labelFormat->setWordWrap(true);

    ui->labelXlsxFilePath->clear();
    ui->labelTsFilePath->clear();

    ui->btnExcelStatus->setVisible(false);
    ui->btnSelectExcel->setStyleSheet("QPushButton{"
                                      "    color: rgb(255, 255, 255);"
                                      "    font-size: 64pt;"
                                      "    font-weight: bold;"
                                      "    border-image: url(:/Resources/button_released.png);"
                                      "}"
                                      "QPushButton:Pressed{border-image: url(:/Resources/button_pressed.png);}");
    ui->btnSelectTs->setStyleSheet(ui->btnSelectExcel->styleSheet());

    ui->btnExcel2Ts->setStyleSheet("QPushButton{"
                                   "    color: rgb(255, 255, 255);"
                                   "    border-image: url(:/Resources/button_released.png);"
                                   "}"
                                   "QPushButton:Pressed{border-image: url(:/Resources/button_pressed.png);}");
    ui->btnTs2Excel->setStyleSheet(ui->btnExcel2Ts->styleSheet());
    ui->btnOpenOutputDir->setStyleSheet(ui->btnExcel2Ts->styleSheet());

    ui->comboBoxFormat->setStyleSheet("QComboBox::drop-down {"
                                      "    image: url(:/Resources/comboBox_dropDown.png);"
                                      "    width: 24px;"
                                      "    padding-right: 12px;"
                                      "}"
                                      "QComboBox {"
                                      "    border-image: url(:/Resources/comboBox.png);"
                                      "    padding-left: 10px;"
                                      "    padding-right: 0px;"
                                      "    color: rgb(255, 255, 255);"
                                      "    font-size: 10pt;"
                                      "}"
                                      "QComboBox QAbstractItemView::item {"
                                      "    height: 40px;"
                                      "    border-image: url(:/Resources/comboBox.png);"
                                      "}");
    ui->comboBoxFormat->setView(new QListView());

    ui->labelFormat->setStyleSheet("QLabel {color: rgb(255, 255, 255);}");

    ui->labelXlsxFilePath->setStyleSheet("QLabel {"
                                         "    color: rgb(255, 255, 255);"
                                         "    font-size: 16pt;"
                                         "}");
    ui->labelTsFilePath->setStyleSheet(ui->labelXlsxFilePath->styleSheet());

    ui->labelXlsxFilePath->setAlignment(Qt::AlignCenter);
    ui->labelXlsxFilePath->setWordWrap(true);

    ui->labelTsFilePath->setAlignment(Qt::AlignCenter);
    ui->labelTsFilePath->setWordWrap(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnSelectExcelClicked()
{
    m_xlsxFilePath = QFileDialog::getOpenFileName(this, "选择Excel文件", "C:\\", "Excel (*.xlsx *xls)");

    if (m_xlsxFilePath.isEmpty())
        return;

    TsExcelHandler::HANDLE_ERROR result = m_tsFixUp->setTranstlationFile(m_xlsxFilePath);

    ui->labelXlsxFilePath->setText(m_xlsxFilePath);

    switch (result) {
    case TsExcelHandler::NORMAL:
        this->setExcelNormalStatus(true);
        return;
    case TsExcelHandler::OPEN_FILE_FAILED:
        m_fileTips = "文件打开失败。";
        break;
    case TsExcelHandler::FORMAT_ERROR:
        m_fileTips = "文件格式错误。";
        break;
    case TsExcelHandler::REPEAT_KEY:
        m_fileTips = "文件存在重复的源文。";
        break;
    default:
        break;
    }

    //TODO：此处调用会导致段错误，待查
//    m_tsFixUp->closeExcelFile();
    this->setExcelNormalStatus(false);

    QMessageBox::information(this, "提示", m_fileTips);
}

void Widget::onBtnSelectTsFileClicked()
{
    m_tsFilePath = QFileDialog::getOpenFileName(this, "选择Ts文件", "C:\\", "Ts (*.ts *.xml)");

    ui->labelTsFilePath->setText(m_tsFilePath);
}

void Widget::onBtnExcel2TsClicked()
{
    if (m_tsFilePath.isEmpty() || m_xlsxFilePath.isEmpty()) {
        QMessageBox::critical(this, "错误", "未选择对应的文件!");
        return;
    }

    QFileInfo fileInfo(m_tsFilePath);

    m_outputFilePath = fileInfo.absoluteDir().path();
#ifdef WIN32
    m_outputFilePath.replace("/", "\\");
#else

#endif
    QString fileBaseName = fileInfo.baseName();
    QString curDateTime  = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    m_tsFixUp->setOutputTsFilePath(m_outputFilePath + fileBaseName + "_" + curDateTime + ".ts");
    m_tsFixUp->setTsFile(m_tsFilePath);

    if (!m_tsFixUp->excel2Ts())
        QMessageBox::critical(this, "错误", "Ts文件完善失败!");
    else
        QMessageBox::information(this, "提示", "转换完成");
}

void Widget::onBtnTs2ExcelClicked()
{
    if (m_tsFilePath.isEmpty()) {
        QMessageBox::critical(this, "错误", "未选择Ts文件!");
        return;
    }

    QFileInfo fileInfo(m_tsFilePath);

    m_outputFilePath = fileInfo.absoluteDir().path();
#ifdef WIN32
    m_outputFilePath.replace("/", "\\");
#else

#endif
    QString fileBaseName = fileInfo.baseName();
    QString curDateTime  = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    m_tsFixUp->setOutputXlsxFilePath(m_outputFilePath + fileBaseName + "_" + curDateTime + ".xlsx");
    m_tsFixUp->setTsFile(m_tsFilePath);

    int columnCount = ui->comboBoxFormat->currentIndex()+2;

    if (!m_tsFixUp->ts2Excel(columnCount))
        QMessageBox::critical(this, "错误", "Ts文件转换失败!");
    else
        QMessageBox::information(this, "提示", "转换完成");
}

void Widget::onBtnOpenOutputClicked()
{
    if (m_tsFilePath.isEmpty())
        QMessageBox::critical(this, "错误", "未选择Ts文件!");
    else {
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_outputFilePath));
    }
}

void Widget::onBtnExcelStatusClicked()
{

}

void Widget::onExcelHandlerError(TsExcelHandler::HANDLE_ERROR errorNum)
{
    switch (errorNum) {
    case TsExcelHandler::OPEN_FILE_FAILED:
        QMessageBox::critical(this, "Error", "Open file failed.");
        break;
    case TsExcelHandler::FORMAT_ERROR:
        QMessageBox::critical(this, "Error", "Excel file's text format is error.");
        break;
    case TsExcelHandler::REPEAT_KEY:
        QMessageBox::critical(this, "Error", "There are duplicate key values.");
        break;
    default:
        break;
    }
}

bool Widget::createFile(const QString &suffix)
{
    if (m_tsFilePath.isEmpty())
        return false;

    QFileInfo fileInfo(m_tsFilePath);

    m_outputFilePath = fileInfo.absoluteDir().path();
#ifdef WIN32
    m_outputFilePath.replace("/", "\\");
#else

#endif
    QString fileBaseName = fileInfo.baseName();
    QString curDateTime  = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");

    if (suffix == ".xlsx")
        m_tsFixUp->setOutputTsFilePath(m_outputFilePath + fileBaseName + "_" + curDateTime + ".xlsx");
    else if (suffix == ".ts")
        m_tsFixUp->setOutputTsFilePath(m_outputFilePath + fileBaseName + "_" + curDateTime + ".ts");
    else
        return false;

    m_tsFixUp->setTsFile(m_tsFilePath);
    return true;
}

void Widget::setExcelNormalStatus(bool isNormal)
{
    ui->btnExcelStatus->setVisible(true);
    if (isNormal)
        ui->btnExcelStatus->setStyleSheet("border-image: url(:/Resources/correct.png);");
    else
        ui->btnExcelStatus->setStyleSheet("border-image: url(:/Resources/warning.png);");
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
