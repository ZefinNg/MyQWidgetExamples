#include "ExcelHandler.h"
#include <QTextStream>
#include <QTextCodec>

ExcelHandler::ExcelHandler(QObject *parent)
    : QObject(parent),
      m_excelFilePath(),
      m_outputFilePath(),
      m_excelRW(new XLSX::ExcelRW(this))
{

}

ExcelHandler::~ExcelHandler()
{

}

void ExcelHandler::setFilePath(const QString &filePath)
{
    m_excelFilePath = filePath;
}

bool ExcelHandler::conver2File(const FILE_TYPE &fileType, const QString& outputFilePath)
{
    m_outputFilePath = outputFilePath;

    switch (fileType) {
    case TS_FILE:
        return this->excel2Ts();
    case TXT_FILE:
        return this->excel2Txt();
    case INI_FILE:
        return this->excel2Ini();
    case XML_FILE:
        return this->excel2Xml();
    default:
        return false;
    }
}

bool ExcelHandler::excel2Ts()
{

}

bool ExcelHandler::excel2Txt()
{
    if (!m_excelRW->openFile(m_excelFilePath)) {
        m_excelRW->save();
        return false;
    }

    QFile txtFile(m_outputFilePath);
    if (!txtFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    int rowCount      = m_excelRW->getRowCount();
    int columnCount   = m_excelRW->getColumnCount();
    int rowStartIndex = m_excelRW->getFirstRow();
    int colStartIndex = m_excelRW->getFirstColumn();

    QTextStream outStream(&txtFile);
    outStream.setCodec(QTextCodec::codecForName("utf-8"));

    QString lineText;

    for (int i = rowStartIndex; i <= rowCount; i++) {
        for (int j = colStartIndex; j <= columnCount; j++) {
            lineText += m_excelRW->getCellText(i, j).toString();

            if (j != columnCount)
                lineText += "|";
        }

        if (i != rowCount)
            outStream << lineText;

        lineText.clear();
    }

    txtFile.close();
    m_excelRW->save();
}

bool ExcelHandler::excel2Ini()
{

}

bool ExcelHandler::excel2Xml()
{

}
