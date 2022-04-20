#include "SourceFileHandler.h"

SourceFileHandler::SourceFileHandler(QObject *parent)
    : QObject(parent),
      m_srcFilePath(),
      m_srcFileType(TS_FILE),
      m_outputFilePath(),
      m_excelRW(new XLSX::ExcelRW(this))
{

}

SourceFileHandler::~SourceFileHandler()
{

}

void SourceFileHandler::setSrcFilePath(const QString filePath, const FILE_TYPE fileType)
{
    m_srcFilePath = filePath;
    m_srcFileType = fileType;
}

bool SourceFileHandler::conver2Excel(const QString outputFilePath)
{
    m_outputFilePath = outputFilePath;

    switch (m_srcFileType) {
    case TS_FILE:
        break;
    case TXT_FILE:
        return this->txt2Excel();
    case INI_FILE:
        break;
    case XML_FILE:
        break;
    default:
        return false;
    };
}

bool SourceFileHandler::txt2Excel()
{
    if (!m_excelRW->openFile(m_outputFilePath))
        return false;

    QFile txtFile(m_srcFilePath);
    if (!txtFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QString eachLine = "";
    QStringList splitList;
    int rowIndex = 1;

    while (!txtFile.atEnd()) {
        eachLine = txtFile.readLine();
        splitList = eachLine.split("|");

        for (int colIndex = 0; colIndex < splitList.size(); colIndex++) {
            if (!m_excelRW->setCellText(rowIndex, colIndex+1, splitList.at(colIndex), QXlsx::Format()))
                break;
        }

        rowIndex++;
    }

    txtFile.close();
    return m_excelRW->save();
}
