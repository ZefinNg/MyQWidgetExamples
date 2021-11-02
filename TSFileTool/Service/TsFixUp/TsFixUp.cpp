﻿#include "TsFixUp.h"

TsFixUp::TsFixUp(QObject *parent)
    : QObject(parent),
      m_fileName(),
      m_outputFile(),
      m_tsFile(new QFile(this)),
      m_domDoc(new QDomDocument()),
      m_excelHandler(new TsExcelHandler(this))
{
//    if (!m_excelHandler->readFile("/home/feng/Desktop/french.csv"))
//        qDebug() << "The csv file read failed.";
//    else
    //        m_translationList = m_excelHandler->classTranslationList();
}

TsFixUp::~TsFixUp()
{
    if (m_domDoc != NULL) {
        delete m_domDoc;
        m_domDoc = NULL;
    }
}

TsExcelHandler::HANDLE_ERROR TsFixUp::setTranstlationFile(const QString xlsxPath)
{
    m_excelHandler->setFilePath(xlsxPath);

    return m_excelHandler->handleTranslation();
}

void TsFixUp::closeExcelFile()
{
    m_excelHandler->closeFile();
}

bool TsFixUp::setTsFile(const QString filePath)
{
    m_fileName = filePath;
    m_tsFile->setFileName(filePath);

    return m_tsFile->open(QIODevice::ReadWrite);
}

void TsFixUp::setOutputTsFile(const QString outputFile)
{
    m_outputFile = outputFile;
    this->createNewTsFile(m_outputFile);
}

bool TsFixUp::excel2Ts()
{
    if (!m_domDoc->setContent(m_tsFile)) {
        qDebug() << "Document set file failed.";
        m_tsFile->close();
        return false;
    }

    QDomElement root = m_domDoc->documentElement();
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
                if (sourceList.at(m).isElement()) {
                    element = sourceList.at(m).toElement();

                    if (element.nodeName() == "source") {
                        source = element.text();
                        translation = m_excelHandler->getTranslation(source);
                        qDebug() << className << "--" << source << "--" << translation;
                    }
                    else if (element.nodeName() == "translation") {
                        if (translation.isEmpty())
                            translation = " ";
                        else
                            element.removeAttribute("type");//找到翻译则删除type属性

                        textTranslation = m_domDoc->createTextNode(translation);
                        element.appendChild(textTranslation);
                        source.clear();
                    }
                    else
                        continue;
                }
            }
        }
    }

    QTextStream outSteam(m_outputTsFile);
    m_domDoc->save(outSteam, 4);
    m_outputTsFile->close();

    m_tsFile->close();

    return true;
}

void TsFixUp::createNewTsFile(QString filePath)
{
    m_outputTsFile = new QFile(this);
    m_outputTsFile->setFileName(filePath);
    if (!m_outputTsFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
        qDebug() << "Create " << m_outputTsFile->fileName() << "failed.";
}