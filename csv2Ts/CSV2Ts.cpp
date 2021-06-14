#include "CSV2Ts.h"

CSV2Ts::CSV2Ts(QObject *parent) : QObject(parent)
{
    m_file         = new QFile(this);
    m_needDealFile = new QFile(this);

    m_needDealFile->setFileName("/home/feng/Desktop/NeedDealFiles/needDeal.csv");

    if (!m_needDealFile->open(QIODevice::ReadWrite)) {
        qDebug() << "Open " << m_needDealFile->fileName() << " failed.";
    }
}

bool CSV2Ts::readFile(QString filePath)
{
    m_file->setFileName(filePath);
    if (!m_file->open(QIODevice::ReadOnly)) {
        qDebug() << "Open " << filePath << "failed.";
        return false;
    }

    QTextStream textStream(m_file);
    QString eachLine = textStream.readLine();

    while (!eachLine.isNull()) {
        this->dealEachLine(eachLine);

        eachLine = textStream.readLine();
    }

    m_needDealFile->close();

    QStringList keysList;

    for (int i = 0; i < m_classTranslationList.count(); i++) {
        qDebug() << m_classTranslationList.at(i).className();
//        for (int j = 0; j < m_classTranslationList.at(i).translationMap().count(); j++) {
//            keysList = m_classTranslationList.at(i).translationMap().keys();
//            foreach (QString eachKey, keysList) {
//                qDebug() << eachKey << m_classTranslationList.at(i).translationMap().value(eachKey);
//            }
//        }
    }

    return true;
}

void CSV2Ts::dealEachLine(QString eachLine)
{
    QStringList textBlockList = eachLine.split(',');
//    qDebug() << textBlockList;

    if (textBlockList.count() >= 3) {
        if (textBlockList.at(0) != "") {
            if (!m_translationBlock.className().isEmpty()) {
                m_classTranslationList.append(m_translationBlock);
                m_translationBlock.clear();
                m_translationBlock.setClassName(textBlockList.at(0));
                m_translationBlock.addMap(textBlockList.at(1), textBlockList.at(2));
            }
            else {
                m_translationBlock.setClassName(textBlockList.at(0));
                m_translationBlock.addMap(textBlockList.at(1), textBlockList.at(2));
            }
        }
        else {
            if (textBlockList.count() == 3)
                m_translationBlock.addMap(textBlockList.at(1), textBlockList.at(2));
            else {
                //存入另一个文件，重新处理
                this->write2File(eachLine);
            }
        }
    }
    else
        this->write2File(eachLine);
}

void CSV2Ts::write2File(QString eachLine)
{
    if (!m_needDealFile->isOpen())
        return;

    QTextStream textStream(m_needDealFile);
    textStream << eachLine << "\n";
}

QList<TranslationBlock> CSV2Ts::classTranslationList() const
{
    return m_classTranslationList;
}

QString CSV2Ts::findTranslation(QString className, QString source)
{
    QMap<QString, QString> map;
    foreach (TranslationBlock each, m_classTranslationList) {
        if (each.className() == className) {
            map = each.translationMap();
            if (map.contains(source))
                return map.value(source);
        }
    }
    return "";
}
