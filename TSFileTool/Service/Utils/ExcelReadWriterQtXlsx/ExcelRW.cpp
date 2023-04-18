#include "ExcelRW.h"

using namespace XLSX;

ExcelRW::ExcelRW(QObject *parent)
    : QObject(parent),
      m_filePath(""),
      m_xlsx(NULL)
{

}

ExcelRW::~ExcelRW()
{

}

bool ExcelRW::openFile(const QString &filePath)
{
build:
    if (m_xlsx == NULL) {
        m_filePath = filePath;
        m_xlsx = new QXlsx::Document(filePath, this);

        return true;
    }
    else {
        m_xlsx->deleteLater();
        m_xlsx = NULL;
        m_filePath = "";
        goto build;
    }
}

QString ExcelRW::getTitle() const
{
    if (m_xlsx == NULL)
        return "";

    return m_xlsx->documentProperty("title");
}

bool ExcelRW::setTitle(const QString &title)
{
    if (m_xlsx == NULL)
        return false;

    m_xlsx->setDocumentProperty("title", title);
    return true;
}

QStringList ExcelRW::getWorksheetNames() const
{
    if (m_xlsx == NULL)
        return QStringList();

    return m_xlsx->sheetNames();
}

bool ExcelRW::selectWorksheet(const QString &name)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->selectSheet(name);
}

QString ExcelRW::getWorkSheetName() const
{
    if (m_xlsx == NULL)
        return "";

    return m_xlsx->currentWorksheet()->sheetName();
}

bool ExcelRW::setWorksheetName(const QString &newName)
{
    if (m_xlsx == NULL)
        return false;

    QString currentSheetName = this->getWorkSheetName();
    return m_xlsx->renameSheet(currentSheetName, newName);
}

bool ExcelRW::addWorksheet(const QString& name)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->addSheet(name);
}

bool ExcelRW::deleteWorksheet(const QString &name)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->deleteSheet(name);
}

int ExcelRW::getRowCount() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().rowCount();
}

int ExcelRW::getColumnCount() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().columnCount();
}

int ExcelRW::getFirstRow() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().firstRow();
}

int ExcelRW::getFirstColumn() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().firstColumn();
}

QVariant ExcelRW::getCellText(const int row, const int col) const
{
    if (m_xlsx == NULL)
        return QVariant();

    if (m_xlsx->cellAt(row, col) == nullptr)
        return QVariant();

    return m_xlsx->cellAt(row, col)->value();
}

bool ExcelRW::setCellText(const int row, const int col, const QString text, const QXlsx::Format format)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->write(row, col, QVariant(text), format);
}

bool ExcelRW::mergeCells(const int firstRow, const int firstColumn, const int lastRow, const int lastColumn)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->mergeCells(QXlsx::CellRange(firstRow, firstColumn, lastRow, lastColumn));
}

bool ExcelRW::save()
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->save();
}

bool ExcelRW::saveAs(const QString &filePath)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->saveAs(filePath);
}

QString ExcelRW::getFilePath() const
{
    return m_filePath;
}
