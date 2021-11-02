#include "ExcelReadWriter.h"
#include <QDebug>

using namespace AXOBJECT;

ExcelReadWrite::ExcelReadWrite(QObject *parent)
    : QObject(parent),
      m_isOpen(false),
      m_filePath(),
      m_excelApp(NULL),
      m_workbooks(NULL),
      m_fileWorkbook(NULL),
      m_worksheets(NULL),
      m_currentWorksheet(NULL),
      m_usedRange(NULL),
      m_rows(NULL),
      m_columns(NULL)
{
    /* ？存疑：
     * 因为QAxObject默认是在单线程下使用的，
     * 因此如果不用以下代码申明多线程,
     * 会导致获取的excel的QAxObject都是NULL
     */
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    //设置m_excelApp为Excel文件的操作对象
    m_excelApp = new QAxObject("Excel.Application");

    //不显示任何警告信息。如果为true, 那么关闭时会出现类似"文件已修改，是否保存"的提示
    m_excelApp->setProperty("DisplayAlerts", true);

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

QString ExcelReadWrite::getTitle()
{
    if (m_isOpen)
        return m_excelApp->property("Caption").toString();

    return "";
}

bool ExcelReadWrite::setTitle(QString title)
{
    if (m_isOpen)
         return m_excelApp->setProperty("Caption", title);

    return false;
}

QString ExcelReadWrite::getWorksheetName()
{
    if (m_isOpen)
        return m_currentWorksheet->property("Name").toString();

    return "";
}

bool ExcelReadWrite::setWorksheetName(QString worksheetName)
{
    if (m_isOpen)
        return m_currentWorksheet->setProperty("Name", worksheetName);

    return false;
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
        m_currentWorksheet = m_worksheets->querySubObject("Item(int)", index);
        m_usedRange        = m_currentWorksheet->querySubObject("UsedRange");
        m_rows             = m_usedRange->querySubObject("Rows");
        m_columns          = m_usedRange->querySubObject("Columns");

        return true;
    }

    return false;
}

void ExcelReadWrite::appendWorksheet()
{
    if (m_isOpen) {
        int worksheetCount = this->getWorksheetCount();
        QAxObject *lastWorksheet = m_worksheets->querySubObject("Item(int)", worksheetCount);
        QAxObject *newWorksheet  = m_worksheets->querySubObject("Add(QVariant)", lastWorksheet->asVariant());
        lastWorksheet->dynamicCall("Move(QVariant)", newWorksheet->asVariant());
    }
}

void ExcelReadWrite::deleteCurrentWorksheet()
{
    if (m_isOpen) {
        m_currentWorksheet->dynamicCall("delete");

        m_currentWorksheet = m_worksheets->querySubObject("Item(int)", 1);
    }
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

bool ExcelReadWrite::setCellText(QString text, int row, int col, ALIGNMENT_H alignmentH, ALIGNMENT_V alignmentV, bool wrap)
{
    if (m_isOpen) {
        QAxObject *cell = m_currentWorksheet->querySubObject("Cells(int, int)", row, col);
        cell->setProperty("Value", text);
        cell->setProperty("HorizontalAlignment", alignmentH);
        cell->setProperty("VerticalAlignment",   alignmentV);
        cell->setProperty("WrapText", wrap);

        return true;
    }

    return false;
}

void ExcelReadWrite::closeFile()
{
    if (m_fileWorkbook != NULL) {
        m_fileWorkbook->dynamicCall("Save()");
        m_fileWorkbook->dynamicCall("Close()");
        m_excelApp->dynamicCall("Quit()");

        m_fileWorkbook = NULL;

        m_isOpen = false;
    }
}
