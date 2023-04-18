#include "Excel2TsWidget.h"
#include "ui_Excel2TsWidget.h"
#include <QMessageBox>

Excel2TsWidget::Excel2TsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Excel2TsWidget),
    m_checkBoxGroup(new QButtonGroup(this)),
    m_clickedIndex(null_Check),
    m_tsFixUp(new TsFixUp(this)),
    m_tsFilePath(),
    m_xlsxFilePath(),
    m_outputFilePath(),
    m_fileTips(),
    m_srcFileHandler(new SourceFileHandler(this))
{
    ui->setupUi(this);

    m_checkBoxGroup->addButton(ui->checkBox2Cols, TwoCols_Check);
    m_checkBoxGroup->addButton(ui->checkBox3Cols, ThreeCols_Check);

    connect(m_checkBoxGroup, SIGNAL(buttonClicked(int)), this, SLOT(onCheckBoxClicked(int)));

    this->initView();

    connect(ui->btnSelectExcel,   SIGNAL(clicked()), this, SLOT(onBtnSelectExcelClicked()));
    connect(ui->btnSelectTs,      SIGNAL(clicked()), this, SLOT(onBtnSelectTsFileClicked()));

    connect(ui->btnExcel2Ts,      SIGNAL(clicked()), this, SLOT(onBtnExcel2TsClicked()));
    connect(ui->btnTs2Excel,      SIGNAL(clicked()), this, SLOT(onBtnTs2ExcelClicked()));
    connect(ui->btnOpenOutputDir, SIGNAL(clicked()), this, SLOT(onBtnOpenOutputClicked()));
}

Excel2TsWidget::~Excel2TsWidget()
{
    delete ui;
}

void Excel2TsWidget::onBtnSelectExcelClicked()
{
    if (m_clickedIndex == null_Check) {
        QMessageBox::critical(this, tr("Error"), tr("Please select the format of excel file."));
        return;
    }

    m_xlsxFilePath = QFileDialog::getOpenFileName(this, tr("Select a Excel file."), "C:\\", "Excel (*.xlsx *xls)");

    if (m_xlsxFilePath.isEmpty())
        return;

    TsExcelHandler::HANDLE_ERROR result = m_tsFixUp->setTranstlationFile(m_xlsxFilePath);

    ui->lineEditExcelPath->setText(m_xlsxFilePath);

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

void Excel2TsWidget::onBtnSelectTsFileClicked()
{
    m_tsFilePath = QFileDialog::getOpenFileName(this, tr("Select a Ts file"), "C:\\", "Ts (*.ts *.xml)");

    ui->lineEditTsPath->setText(m_tsFilePath);

    m_srcFileHandler->setSrcFilePath(m_tsFilePath);
}

void Excel2TsWidget::onBtnExcel2TsClicked()
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

void Excel2TsWidget::onBtnTs2ExcelClicked()
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
#if 0
    m_tsFixUp->setOutputXlsxFilePath(m_outputFilePath + fileBaseName + "_" + curDateTime + ".xlsx");
    m_tsFixUp->setTsFile(m_tsFilePath);

    if (!m_tsFixUp->ts2Excel(m_clickedIndex))
#else
    if (!m_srcFileHandler->conver2Excel(m_outputFilePath + "\\" + fileBaseName + "_" + curDateTime + ".xlsx"))
#endif
        QMessageBox::critical(this, "错误", "Ts文件转换失败!");
    else
        QMessageBox::information(this, "提示", "转换完成");
}

void Excel2TsWidget::onBtnOpenOutputClicked()
{
    if (m_tsFilePath.isEmpty())
        QMessageBox::critical(this, "错误", "未选择Ts文件!");
    else
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_outputFilePath));
}

void Excel2TsWidget::onBtnExcelStatusClicked()
{

}

void Excel2TsWidget::onCheckBoxClicked(int index)
{
    (CheckBox_Index)index > null_Check ? m_clickedIndex = (CheckBox_Index)index : m_clickedIndex = TwoCols_Check;
}

void Excel2TsWidget::onExcelHandlerError(TsExcelHandler::HANDLE_ERROR errorNum)
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

void Excel2TsWidget::initView()
{
    this->setWindowTitle("TSFileTool");
    //与.pro中的RC_ICONS效果一样
//    this->setWindowIcon(QIcon(":/Resources/icon.ico"));
    this->setStyleSheet("#widget{border-image: url(:/Resources/background.png);}"
                        "#checkBox2Cols,#checkBox3Cols{color:rgb(255, 255, 255);}");

    ui->checkBox2Cols->setChecked(true);
    m_clickedIndex = TwoCols_Check;

    ui->labelFormat->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->labelFormat->setWordWrap(true);

    ui->lineEditExcelPath->setEnabled(false);
    ui->lineEditTsPath->setEnabled(false);

    ui->lineEditExcelPath->clear();
    ui->lineEditTsPath->clear();

    ui->btnExcelStatus->setVisible(false);
    ui->btnSelectExcel->setStyleSheet("QPushButton{"
                                      "    color: rgb(255, 255, 255);"
                                      "    font-size: 18pt;"
                                      "    font-weight: bold;"
                                      "    border-image: url(:/Resources/button_released.png);"
                                      "}"
                                      "QPushButton:Pressed{border-image: url(:/Resources/button_pressed.png);}");
    ui->btnSelectTs->setStyleSheet(ui->btnSelectExcel->styleSheet());

    ui->btnOpenOutputDir->setStyleSheet("QPushButton{"
                                        "    color: rgb(255, 255, 255);"
                                        "    border-image: url(:/Resources/button_released.png);"
                                        "}"
                                        "QPushButton:Pressed{border-image: url(:/Resources/button_pressed.png);}");

    ui->btnExcel2Ts->setStyleSheet("QPushButton {"
                                   "    border-image: url(:/Resources/toRight.png);"
                                   "}"
                                   "QPushButton:Pressed{border-image: url(:/Resources/toRight_pressed.png)}");
    ui->btnTs2Excel->setStyleSheet("QPushButton {"
                                   "    border-image: url(:/Resources/toLeft.png);"
                                   "}"
                                   "QPushButton:Pressed{border-image: url(:/Resources/toLeft_pressed.png)}");

    ui->labelFormat->setStyleSheet("QLabel {color: rgb(255, 255, 255);}");

    ui->lineEditExcelPath->setStyleSheet("QLineEdit {"
                                         "    color: rgb(255, 255, 255);"
                                         "    background-color: rgb(20, 138, 225);"
                                         "    font-size: 8pt;"
                                         "}");
    ui->lineEditTsPath->setStyleSheet(ui->lineEditExcelPath->styleSheet());

    ui->lineEditExcelPath->setAlignment(Qt::AlignCenter);
    ui->lineEditTsPath->setAlignment(Qt::AlignCenter);
}

bool Excel2TsWidget::createFile(const QString &suffix)
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

void Excel2TsWidget::setExcelNormalStatus(bool isNormal)
{
    ui->btnExcelStatus->setVisible(true);
    if (isNormal)
        ui->btnExcelStatus->setStyleSheet("border-image: url(:/Resources/correct.png);");
    else
        ui->btnExcelStatus->setStyleSheet("border-image: url(:/Resources/warning.png);");

}
