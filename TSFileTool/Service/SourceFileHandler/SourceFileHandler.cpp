#include "SourceFileHandler.h"
#include <QTextCodec>

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
        return this->ts2Excel();
    case TXT_FILE:
        return this->txt2Excel();
    case INI_FILE:
        return this->ini2Excel();
    case XML_FILE:
        return this->xml2Excel();
    default:
        return false;
    };
}

bool SourceFileHandler::ts2Excel(const int &columns)
{
    if (!m_excelRW->openFile(m_outputFilePath))
        return false;

    QFile tsFile(m_srcFilePath);
    if (!tsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_excelRW->save();
        return false;
    }

    QDomDocument domDoc;
    domDoc.setContent(&tsFile);

    QDomElement root = domDoc.documentElement();
    QDomNodeList contextList = root.childNodes();
    QDomNodeList nameMessageList, sourceList, translationList;
    QDomElement  element;
    QDomText textTranslation;
    QString className, source, translation;

    int row = 1, col = 1;
    int classRow = row;

    for (int i = 0; i < contextList.count(); i++) {
        nameMessageList = contextList.at(i).childNodes();

        for (int j = 0; j < nameMessageList.count(); j++) {
            if (nameMessageList.at(j).nodeName() == "name") {
                element = nameMessageList.at(j).toElement();
                className = element.text();

                m_excelRW->setCellText(row, col, className);

                if (columns == 3) {
                    if (classRow < row) {
                        m_excelRW->mergeCells(classRow, col, row-1, col);
                        classRow = row;
                    }
                }
            }

            sourceList = nameMessageList.at(j).childNodes();

            for (int m = 0; m < sourceList.count(); m++) {
                if (sourceList.at(m).isElement()) {
                    element = sourceList.at(m).toElement();

                    if (element.nodeName() == "source") {
                        source = element.text();

                        if (columns == 3)
                            m_excelRW->setCellText(row, col+1, source);
                        else
                            m_excelRW->setCellText(row, col, source);

                        row++;
                    }
                    else
                        continue;
                }
            }
        }
    }

    tsFile.close();
    return m_excelRW->save();
}

bool SourceFileHandler::txt2Excel()
{
    if (!m_excelRW->openFile(m_outputFilePath)) {
        m_excelRW->save();
        return false;
    }

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
            if (!m_excelRW->setCellText(rowIndex, colIndex+1, splitList.at(colIndex)))
                break;
        }

        rowIndex++;
    }

    txtFile.close();
    return m_excelRW->save();
}

bool SourceFileHandler::ini2Excel()
{
    if (!m_excelRW->openFile(m_outputFilePath)) {
        m_excelRW->save();
        return false;
    }

    int rowIndex = 1, columnIndex = 1;

    QSettings iniFile(m_srcFilePath, QSettings::IniFormat);
    iniFile.setIniCodec(QTextCodec::codecForName("utf-8"));
    foreach (QString group, iniFile.childGroups()) {
        iniFile.beginGroup(group);

        m_excelRW->setCellText(rowIndex, columnIndex, group);

        foreach (QString key, iniFile.childKeys())
            m_excelRW->setCellText(rowIndex, ++columnIndex, iniFile.value(key).toString());

        rowIndex++;
        columnIndex = 1;
        iniFile.endGroup();
    }

    return m_excelRW->save();
}

bool SourceFileHandler::xml2Excel()
{
    return false;
}
