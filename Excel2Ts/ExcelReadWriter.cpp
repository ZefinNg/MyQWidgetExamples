#include "ExcelReadWriter.h"
#include <QDebug>

ExcelReadWrite::ExcelReadWrite(QObject *parent) : QObject(parent)
{
    m_isOpen       = false;
    m_filePath     = "";
    m_excelApp     = NULL;
    m_workbooks    = NULL;
    m_fileWorkbook = NULL;
    m_workSheets   = NULL;

    //设置m_excelApp为Excel文件的操作对象
    m_excelApp = new QAxObject("Excel.Application");

    //如果为true，则会出现MS Excel的界面，反之则不出现
    m_excelApp->dynamicCall("SetVisible(bool)", false);

    m_workbooks = m_excelApp->querySubObject("WorkBooks");
}

ExcelReadWrite::~ExcelReadWrite()
{
    this->closeFile();

    if (m_excelApp != NULL) {
        delete m_excelApp;
        m_excelApp = NULL;
    }
}

bool ExcelReadWrite::isOpen()
{
    return m_isOpen;
}

bool ExcelReadWrite::openFile(QString filePath)
{
    QFile file(filePath);
    if (!file.exists())
        return false;

    m_filePath = filePath;

    //打开指定路径的excel文件
    m_fileWorkbook = m_workbooks->querySubObject("Open(QString&)", filePath);

    if (m_fileWorkbook == NULL)
        return false;

    m_isOpen = true;

    //获取打开的excel文件的所有工作表，也可以使用"Sheets"
    m_workSheets = m_fileWorkbook->querySubObject("WorkSheets");

    return true;
}

QString ExcelReadWrite::title()
{
    if (m_isOpen)
        return m_excelApp->property("Caption").toString();

    return "";
}

QString ExcelReadWrite::getWorkSheetName()
{
    if (m_isOpen)
        return m_workSheets->property("Name").toString();

    return "";

}

int ExcelReadWrite::getWorkSheetCount()
{
    if (m_isOpen)
        return m_workSheets->property("Count").toInt();

    return -1;
}

bool ExcelReadWrite::setCurrentWorkSheet(int index)
{
    if (m_isOpen && index <= this->getWorkSheetCount()) {
        m_workSheets = m_fileWorkbook->querySubObject("Sheets(int", index);
        return true;
    }

    return false;
}

int ExcelReadWrite::getRows()
{
    if (m_isOpen)
        return 3;

    return -1;
}

int ExcelReadWrite::getColumns()
{

}

void ExcelReadWrite::closeFile()
{
    if (m_fileWorkbook != NULL) {
        m_fileWorkbook->dynamicCall("Close()");
        m_excelApp->dynamicCall("Quit()");

        m_fileWorkbook = NULL;

        m_isOpen = false;
    }
}

QString ExcelReadWrite::getCellText(int row, int col)
{

}
