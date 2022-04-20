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
    m_btnSelectErrorFile(new QPushButton(tr("Select Txt"), this)),
    m_lineEditErrorFilePath(new QLineEdit(this)),
    m_btnExcel2Txt(new QPushButton(tr("E2T"), this)),
    m_btnTxt2Excel(new QPushButton(tr("T2E"), this)),
    m_excelFile(),
    m_errorFile(),
    m_srcFileHandler(new SourceFileHandler(this))
{
    ui->setupUi(this);

    this->initView();

    connect(m_btnSelectExcel, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnSelectExcelClicked);
    connect(m_btnSelectErrorFile, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnSecectErrorFileClicked);

    connect(m_btnExcel2Txt, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnExcel2ErrorFileClicked);
    connect(m_btnTxt2Excel, &QPushButton::clicked, this, &Excel2ErrorFileWidget::onBtnErrorFile2ExcelClicked);
}

Excel2ErrorFileWidget::~Excel2ErrorFileWidget()
{
    delete ui;
}

void Excel2ErrorFileWidget::onBtnSelectExcelClicked()
{
    m_excelFile = QFileDialog::getOpenFileName(this, tr("Select a ErrorNum file."), "C:\\", "Excel (*.xlsx *xls)");
    m_lineEditExcelPath->setText(m_excelFile);
}

void Excel2ErrorFileWidget::onBtnSecectErrorFileClicked()
{
    m_errorFile = QFileDialog::getOpenFileName(this, tr("Select a ErrorNum file."), "C:\\", "txt (*.ini *.txt)");
    m_lineEditErrorFilePath->setText(m_errorFile);

    m_srcFileHandler->setSrcFilePath(m_errorFile, SourceFileHandler::TXT_FILE);
}

void Excel2ErrorFileWidget::onBtnExcel2ErrorFileClicked()
{

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

    QHBoxLayout *errorFileLayout = new QHBoxLayout();
    errorFileLayout->addWidget(m_btnSelectErrorFile);
    errorFileLayout->addWidget(m_lineEditErrorFilePath);

    QHBoxLayout *btnConverLayout = new QHBoxLayout();
    btnConverLayout->addStretch();
    btnConverLayout->addWidget(m_btnExcel2Txt);
    btnConverLayout->addWidget(m_btnTxt2Excel);
    btnConverLayout->addStretch();

    widgetLayout->addLayout(excelLayout);
    widgetLayout->addLayout(errorFileLayout);
    widgetLayout->addLayout(btnConverLayout);
}

void Excel2ErrorFileWidget::drawView()
{
    m_lineEditExcelPath->setEnabled(false);
    m_lineEditErrorFilePath->setEnabled(false);
}
