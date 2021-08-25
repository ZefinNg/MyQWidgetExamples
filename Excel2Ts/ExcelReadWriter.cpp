#include "ExcelReadWriter.h"

ExcelReadWrite::ExcelReadWrite(QString filePath, QObject *parent) : QObject(parent)
{
    m_excelApp     = NULL;
    m_workbooks    = NULL;
    m_fileWorkbook = NULL;
    m_workSheets   = NULL;

    //设置m_excelApp为Excel文件的操作对象
    m_excelApp = new QAxObject("Excel.Application");

    //如果为true，则会出现MS Excel的界面，反之则不出现
    m_excelApp->dynamicCall("SetVisible(bool)", false);

    m_workbooks    = m_excelApp->querySubObject("WorkBooks");

    //打开指定路径的excel文件
    m_fileWorkbook = m_workbooks->querySubObject("Open(QString&)", filePath);

    //获取打开的excel文件的所有工作表
    m_workSheets   = m_fileWorkbook->querySubObject("WorkSheets");
}

ExcelReadWrite::~ExcelReadWrite()
{
    this->closeFile();

    if (m_fileWorkbook != NULL) {
        delete m_fileWorkbook;
        m_fileWorkbook = NULL;
    }

    if (m_workSheets != NULL) {
        delete m_workSheets;
        m_workSheets = NULL;
    }

    if (m_workbooks != NULL) {
        delete m_workbooks;
        m_workbooks = NULL;
    }
}

QString ExcelReadWrite::title()
{
    return m_excelApp->property("Caption").toString();
}

int ExcelReadWrite::getWorkSheetCount()
{
    if (m_workbooks != NULL)
        return m_workSheets->property("Count").toInt();

    return -1;
}

void ExcelReadWrite::setCurrentWorkSheet(int index)
{

}

int ExcelReadWrite::getRows()
{

}

int ExcelReadWrite::getColumns()
{

}

void ExcelReadWrite::closeFile()
{
    if (m_fileWorkbook != NULL) {
        m_fileWorkbook->dynamicCall("Close()");
        m_excelApp->dynamicCall("Quit()");

        if (m_excelApp != NULL) {
            delete m_excelApp;
            m_excelApp = NULL;
        }
    }
}

QString ExcelReadWrite::getCellText(int row, int col)
{

}
