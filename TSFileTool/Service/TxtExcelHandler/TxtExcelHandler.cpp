#include "TxtExcelHandler.h"

TxtExcelHandler::TxtExcelHandler(QObject *parent)
    : QObject(parent),
      m_filePath(),
      m_excelRW(new XLSX::ExcelRW(this))
{

}

TxtExcelHandler::~TxtExcelHandler()
{

}

void TxtExcelHandler::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

void TxtExcelHandler::closeFile()
{
    m_filePath = "";

}

bool TxtExcelHandler::setOutputExcelFile(const QString &filePath)
{
    QFile file(filePath);
    bool result = false;

    if (!file.exists()) {
        result = file.open(QIODevice::WriteOnly);
        file.close();
    }

    if (result)
        return m_excelRW->openFile(filePath);

    return false;
}

bool TxtExcelHandler::writeCell(const QString text, const int row, const int column, QXlsx::Format format)
{
    if (m_excelRW->getFilePath().isEmpty())
        m_excelRW->openFile(m_filePath);

    return m_excelRW->setCellText(row, column, text, format);
}
