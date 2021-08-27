#include "ExcelHandler.h"

ExcelHandler::ExcelHandler(QObject *parent) : QObject(parent)
{
    m_excelRW = new ExcelReadWrite(this);
}

ExcelHandler::EXCEL_HANDLE_ERROR ExcelHandler::handleFile(QString filePath)
{
    if (!m_excelRW->openFile(filePath))
        return OPEN_FILE_FAILED;

}
