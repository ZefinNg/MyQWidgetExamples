#include "ErrorTxtFixUp.h"

ErrorTxtFixUp::ErrorTxtFixUp(QObject *parent)
    : QObject(parent),
      m_file(new QFile(this)),
      m_filePath(),
      m_contextList()
{

}

ErrorTxtFixUp::~ErrorTxtFixUp()
{

}

bool ErrorTxtFixUp::openFile(const QString &filePath)
{
    m_filePath = filePath;
    m_file->setFileName(m_filePath);

    return m_file->open(QIODevice::ReadOnly | QIODevice::Text);
}

bool ErrorTxtFixUp::fixUpFile()
{
    QString eachString;
    QString number;
    QString numTips;
    QString numInfo;

    while (!m_file->atEnd()) {
        eachString = m_file->readLine();
        number = this->getNum(eachString);
    }

    return true;
}

void ErrorTxtFixUp::setOutputFile(const QString &newFilePath)
{

}

QString ErrorTxtFixUp::getNum(const QString &text)
{
    return text.left(text.indexOf("|"));
}
