#include "ExcelReadWriter.h"

using namespace XLSX;

ExcelReadWriter::ExcelReadWriter(QObject *parent)
    : QObject(parent),
      m_filePath(""),
      m_xlsx(NULL)
{

}

ExcelReadWriter::~ExcelReadWriter()
{

}

bool ExcelReadWriter::openFile(const QString &filePath)
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

QString ExcelReadWriter::getTitle() const
{
    if (m_xlsx == NULL)
        return "";

    return m_xlsx->documentProperty("title");
}

bool ExcelReadWriter::setTitle(const QString &title)
{
    if (m_xlsx == NULL)
        return false;

    m_xlsx->setDocumentProperty("title", title);
    return true;
}

QStringList ExcelReadWriter::getWorksheetNames() const
{
    if (m_xlsx == NULL)
        return QStringList();

    return m_xlsx->sheetNames();
}

bool ExcelReadWriter::selectWorksheet(const QString &name)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->selectSheet(name);
}

QString ExcelReadWriter::getWorkSheetName() const
{
    if (m_xlsx == NULL)
        return "";

    return m_xlsx->currentWorksheet()->sheetName();
}

bool ExcelReadWriter::setWorksheetName(const QString &newName)
{
    if (m_xlsx == NULL)
        return false;

    QString currentSheetName = this->getWorkSheetName();
    return m_xlsx->renameSheet(currentSheetName, newName);
}

bool ExcelReadWriter::addWorksheet(const QString& name)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->addSheet(name);
}

bool ExcelReadWriter::deleteWorksheet(const QString &name)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->deleteSheet(name);
}

int ExcelReadWriter::getRowCount() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().rowCount();
}

int ExcelReadWriter::getColumnCount() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().columnCount();
}

int ExcelReadWriter::getFirstRow() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().firstRow();
}

int ExcelReadWriter::getFirstColumn() const
{
    if (m_xlsx == NULL)
        return -1;

    return m_xlsx->dimension().firstColumn();
}

QVariant ExcelReadWriter::getCellText(const int row, const int col) const
{
    if (m_xlsx == NULL)
        return QVariant();

    return m_xlsx->cellAt(row, col)->value();
}

bool ExcelReadWriter::setCellText(const int row, const int col, const QString text, const QXlsx::Format format)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->write(row, col, QVariant(text), format);
}

bool ExcelReadWriter::save()
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->save();
}

bool ExcelReadWriter::saveAs(const QString &filePath)
{
    if (m_xlsx == NULL)
        return false;

    return m_xlsx->saveAs(filePath);
}
