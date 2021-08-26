#include "ExcelReadWriter.h"
#include <QDebug>

ExcelReadWrite::ExcelReadWrite(QObject *parent) : QObject(parent)
{
    m_isOpen           = false;
    m_filePath         = "";
    m_excelApp         = NULL;
    m_workbooks        = NULL;
    m_fileWorkbook     = NULL;
    m_worksheets       = NULL;
    m_currentWorksheet = NULL;
    m_usedRange        = NULL;

    //设置m_excelApp为Excel文件的操作对象
    m_excelApp = new QAxObject("Excel.Application");

    //如果为true，则会出现Ms Excel的界面，反之则不出现
    m_excelApp->dynamicCall("SetVisible(bool)", false);

    //也可以使用参数"ActiveWorkBook"
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

    //打开指定路径的excel文件
    m_fileWorkbook = m_workbooks->querySubObject("Open(QString&)", filePath);

    if (m_fileWorkbook == NULL)
        return false;

    m_filePath = filePath;
    m_isOpen   = true;

    //获取打开的excel文件的所有工作表，也可以使用"Sheets"
    m_worksheets = m_fileWorkbook->querySubObject("WorkSheets");

    //默认设置为操作第一张工作表
    m_currentWorksheet = m_worksheets->querySubObject("Item(int)", 1);

    //
    m_usedRange        = m_currentWorksheet->querySubObject("UsedRange");

    m_rows             = m_usedRange->querySubObject("Rows");
    m_columns          = m_usedRange->querySubObject("Columns");

    return true;
}

QString ExcelReadWrite::title()
{
    if (m_isOpen)
        return m_excelApp->property("Caption").toString();

    return "";
}

QString ExcelReadWrite::getWorksheetName()
{
    if (m_isOpen)
        return m_currentWorksheet->property("Name").toString();

    return "";

}

int ExcelReadWrite::getWorksheetCount()
{
    if (m_isOpen)
        return m_worksheets->property("Count").toInt();

    return -1;
}

bool ExcelReadWrite::setCurrentWorkSheet(int index)
{
    if (m_isOpen && index > 0 && index <= this->getWorksheetCount()) {
        m_currentWorksheet = m_fileWorkbook->querySubObject("Sheets(int", index);
        m_usedRange        = m_currentWorksheet->querySubObject("UsedRange");
        m_rows             = m_usedRange->querySubObject("Rows");
        m_columns          = m_usedRange->querySubObject("Columns");

        return true;
    }

    return false;
}

int ExcelReadWrite::getRows()
{
    if (m_isOpen) {
        QAxObject *rowsObject = m_usedRange->querySubObject("Rows");
        return rowsObject->property("Count").toInt();
    }

    return -1;
}

int ExcelReadWrite::getColumns()
{
    if (m_isOpen) {
        QAxObject *columnsObject = m_usedRange->querySubObject("Columns");
        return columnsObject->property("Count").toInt();
    }

    return -1;
}

int ExcelReadWrite::getStartRows()
{
    if (m_isOpen)
        return m_usedRange->property("Row").toInt();

    return -1;
}

int ExcelReadWrite::getStartColumns()
{
    if (m_isOpen)
        return m_usedRange->property("Column").toInt();

    return -1;
}

QString ExcelReadWrite::getCellText(int row, int col)
{
    if (!m_isOpen)
        return "";

    QAxObject *cell = m_currentWorksheet->querySubObject("Cells(int, int)", row, col);
    return cell->property("Value").toString();
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
