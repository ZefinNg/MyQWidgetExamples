#include "TxtExcelHandler.h"

TxtExcelHandler::TxtExcelHandler(QObject *parent)
    : QObject(parent),
      m_filePath(),
      m_excelRW(new XLSX::ExcelReadWriter(this))
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
