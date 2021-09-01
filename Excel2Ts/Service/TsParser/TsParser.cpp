#include "TsParser.h"

TsParser::TsParser(QObject *parent)
    : QObject(parent),
      m_fileName(),
      m_outputFile(),
      m_tsFile(new QFile(this)),
      m_excelHandler(new ExcelHandler(this)),
      m_translationMapper()
{
//    if (!m_excelHandler->readFile("/home/feng/Desktop/french.csv"))
//        qDebug() << "The csv file read failed.";
//    else
//        m_translationList = m_excelHandler->classTranslationList();
}

ExcelHandler::HANDLE_ERROR TsParser::setExcelFile(const QString filePath)
{
    m_excelHandler->setFilePath(filePath);

    return m_excelHandler->handleFile();
}

bool TsParser::setTsFile(const QString filePath)
{
    m_fileName = filePath;
    m_tsFile->setFileName(filePath);

    return m_tsFile->open(QIODevice::ReadWrite);
}

void TsParser::setOutputTsFile(const QString outputFile)
{
    m_outputFile = outputFile;
    this->createNewTsFile(m_outputFile);
}

bool TsParser::fixUpTsFile()
{
    QDomDocument tsDoc;
    if (!tsDoc.setContent(m_tsFile)) {
        qDebug() << "Document set file failed.";
        m_tsFile->close();
        return false;
    }

    QDomElement root = tsDoc.documentElement();
    qDebug() << "root tag name:" << root.tagName();
    qDebug() << "root node name:" << root.nodeName();

    QDomNodeList contextList = root.childNodes();
    QDomNodeList nameMessageList, sourceList, translationList;
    QDomElement  element;
    QString className, source, translation;
    QDomText textTranslation;

    for (int i = 0; i < contextList.count(); i++) {
//        qDebug() << i << contextList.at(i).nodeName();
        nameMessageList = contextList.at(i).childNodes();

        for (int j = 0; j < nameMessageList.count(); j++) {
//            qDebug() << j << nameMessageList.at(j).nodeName();
            //找出className
            if (nameMessageList.at(j).nodeName() == "name") {
                element = nameMessageList.at(j).toElement();
                className = element.text();
//                qDebug() << "name:" << className;
            }

            sourceList = nameMessageList.at(j).childNodes();

            for (int m = 0; m < sourceList.count(); m++) {
#if 1
                if (sourceList.at(m).isElement()) {
                    element = sourceList.at(m).toElement();

                    if (element.nodeName() == "source") {
                        source = element.text();
                        translation = m_excelHandler->findTranslation(className, source);
                        qDebug() << className << "--" << source << "--" << translation;
                    }
                    else if (element.nodeName() == "translation") {
                        if (!translation.isEmpty()) {
                            textTranslation = tsDoc.createTextNode(translation);
                            element.appendChild(textTranslation);
                            source.clear();
                        }
                    }
                    else
                        continue;
                }
#else
                if (sourceList.at(m).nodeName() == "source") {
                    element = sourceList.at(m).toElement();
                    source = element.text();
                    translation = m_csv2Ts->findTranslation(className, source);
                }
                else if (sourceList.at(m).nodeName() == "translation") {
                    element = sourceList.at(m).toElement();
                    qDebug() << element.attribute("type");
                    source.clear();
                }
                else
                    continue;
#endif
            }
        }
    }

    QTextStream outSteam(m_outputTsFile);
    tsDoc.save(outSteam, 4);
    m_outputTsFile->close();

    m_tsFile->close();
}

void TsParser::createNewTsFile(QString filePath)
{
    m_outputTsFile = new QFile(this);
    m_outputTsFile->setFileName(filePath);
    if (!m_outputTsFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
        qDebug() << "Create " << m_outputTsFile->fileName() << "failed.";
}
