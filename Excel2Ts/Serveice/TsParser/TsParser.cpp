#include "TsParser.h"

TsParser::TsParser(QObject *parent) : QObject(parent)
{
    m_fileName = "";
    m_tsFile   = new QFile(this);
    m_csv2Ts   = new CSV2Ts(this);

    if (!m_csv2Ts->readFile("/home/feng/Desktop/french.csv"))
        qDebug() << "The csv file read failed.";
    else
        m_translationList = m_csv2Ts->classTranslationList();

    this->createNewTsFile("/home/feng/Desktop/french_new.ts");
}

void TsParser::setFilePath(QString filePath)
{
    m_fileName = filePath;
    m_tsFile->setFileName(filePath);

    if (!m_tsFile->open(QIODevice::ReadWrite)) {
        qDebug() << "Open " << m_fileName << "failed.";
        return;
    }

    QDomDocument tsDoc;
    if (!tsDoc.setContent(m_tsFile)) {
        qDebug() << "Document set file failed.";
        m_tsFile->close();
        return;
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
                        translation = m_csv2Ts->findTranslation(className, source);
//                        qDebug() << className << "--" << source << "--" << translation;
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

    QTextStream outSteam(m_newTsFile);
    tsDoc.save(outSteam, 4);
    m_newTsFile->close();

    m_tsFile->close();
}

void TsParser::createNewTsFile(QString filePath)
{
    m_newTsFile = new QFile(this);
    m_newTsFile->setFileName(filePath);
    if (!m_newTsFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
        qDebug() << "Create " << m_newTsFile->fileName() << "failed.";
}
