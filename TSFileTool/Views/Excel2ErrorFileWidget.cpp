#include "Excel2ErrorFileWidget.h"
#include "ui_Excel2ErrorFileWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

Excel2ErrorFileWidget::Excel2ErrorFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Excel2ErrorFileWidget),
    m_btnSelectExcel(new QPushButton(tr("Select Excel"), this)),
    m_lineEditExcelPath(new QLineEdit(this)),
    m_btnSelectTxt(new QPushButton(tr("Select Txt"), this)),
    m_lineEditTxtPath(new QLineEdit(this)),
    m_btnSelectIni(new QPushButton(tr("Select Ini"), this)),
    m_lineEditIniPath(new QLineEdit(this)),
    m_btnExcel2ErrorFile(new QPushButton(tr("E2T"), this)),
    m_btnErrorFile2Excel(new QPushButton(tr("T2E"), this)),
    m_excelFile(),
    m_errorFile(),
    m_srcFileHandler(new SourceFileHandler(this)),
    m_excelHandler(new ExcelHandler(this))
{
    ui->setupUi(this);

    this->initView();

    connect(m_btnSelectExcel, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnSelectExcelClicked);
    connect(m_btnSelectTxt,   &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnSelectTxtFileClicked);
    connect(m_btnSelectIni,   &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnSelectIniFileClicked);

    connect(m_btnExcel2ErrorFile, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnExcel2ErrorFileClicked);
    connect(m_btnErrorFile2Excel, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnErrorFile2ExcelClicked);
}

Excel2ErrorFileWidget::~Excel2ErrorFileWidget()
{
    delete ui;
}

void Excel2ErrorFileWidget::onBtnSelectExcelClicked()
{
    m_excelFile = QFileDialog::getOpenFileName(this, tr("Select a ErrorNum file."), "C:\\", "Excel (*.xlsx *xls)");
    m_lineEditExcelPath->setText(m_excelFile);

    m_excelHandler->setFilePath(m_excelFile);
}

void Excel2ErrorFileWidget::onBtnSelectTxtFileClicked()
{
    m_errorFile = QFileDialog::getOpenFileName(this, tr("Select a ErrorNum file."), "C:\\", "txt (*.ini *.txt)");
    m_lineEditTxtPath->setText(m_errorFile);

    m_srcFileHandler->setSrcFilePath(m_errorFile, SourceFileHandler::TXT_FILE);
}

void Excel2ErrorFileWidget::onBtnSelectIniFileClicked()
{
    m_errorFile = QFileDialog::getOpenFileName(this, tr("Select a ErrorNum file."), "C:\\", "ini (*.ini)");
    m_lineEditIniPath->setText(m_errorFile);

    m_srcFileHandler->setSrcFilePath(m_errorFile, SourceFileHandler::INI_FILE);
}

void Excel2ErrorFileWidget::onBtnExcel2ErrorFileClicked()
{
    QFileInfo excelInfo(m_excelFile);

    m_outputFilePath = excelInfo.absoluteDir().path();

#ifdef WIN32
    m_outputFilePath.replace("/", "\\");
#else

#endif
    QString fileBaseName = excelInfo.baseName();
    QString curDateTime  = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    QString disPath = m_outputFilePath + "\\" + fileBaseName + "_" + curDateTime + ".txt";

    if (m_excelHandler->conver2File(ExcelHandler::TXT_FILE, disPath))
        QMessageBox::information(this, tr("Tips"), tr("Conversion is complete."));
    else
        QMessageBox::critical(this, tr("Error"), tr("File conversion to Excel failed."));
}

void Excel2ErrorFileWidget::onBtnErrorFile2ExcelClicked()
{
    QFileInfo fileInfo(m_errorFile);

    m_outputFilePath = fileInfo.absoluteDir().path();

#ifdef WIN32
    m_outputFilePath.replace("/", "\\");
#else

#endif
    QString fileBaseName = fileInfo.baseName();
    QString curDateTime  = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    QString disPath = m_outputFilePath + "\\" + fileBaseName + "_" + curDateTime + ".xlsx";

    if (m_srcFileHandler->conver2Excel(disPath))
        QMessageBox::information(this, tr("Tips"), tr("Conversion is complete."));
    else
        QMessageBox::critical(this, tr("Error"), tr("File conversion to Excel failed."));
}

void Excel2ErrorFileWidget::initView()
{
    this->layoutView();
    this->drawView();
}

void Excel2ErrorFileWidget::layoutView()
{
    QVBoxLayout *widgetLayout = new QVBoxLayout(this);

    QHBoxLayout *excelLayout = new QHBoxLayout();
    excelLayout->addWidget(m_btnSelectExcel);
    excelLayout->addWidget(m_lineEditExcelPath);

    QHBoxLayout *txtFileLayout = new QHBoxLayout();
    txtFileLayout->addWidget(m_btnSelectTxt);
    txtFileLayout->addWidget(m_lineEditTxtPath);

    QHBoxLayout *iniFileLayout = new QHBoxLayout();
    iniFileLayout->addWidget(m_btnSelectIni);
    iniFileLayout->addWidget(m_lineEditIniPath);

    QHBoxLayout *btnConverLayout = new QHBoxLayout();
    btnConverLayout->addStretch();
    btnConverLayout->addWidget(m_btnExcel2ErrorFile);
    btnConverLayout->addWidget(m_btnErrorFile2Excel);
    btnConverLayout->addStretch();

    widgetLayout->addLayout(excelLayout);
    widgetLayout->addLayout(txtFileLayout);
    widgetLayout->addLayout(iniFileLayout);
    widgetLayout->addLayout(btnConverLayout);
}

void Excel2ErrorFileWidget::drawView()
{
    m_lineEditExcelPath->setEnabled(false);
    m_lineEditTxtPath->setEnabled(false);
    m_lineEditIniPath->setEnabled(false);
}
