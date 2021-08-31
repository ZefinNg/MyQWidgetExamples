#include "TranslationBlock.h"

TranslationBlock::TranslationBlock()
{
    m_className = "";
    m_translationMap.clear();
}

QString TranslationBlock::className() const
{
    return m_className;
}

void TranslationBlock::setClassName(const QString &className)
{
    m_className = className;
}

QMap<QString, QString> TranslationBlock::translationMap() const
{
    return m_translationMap;
}

void TranslationBlock::setTranslationMap(const QMap<QString, QString> &translationMap)
{
    m_translationMap = translationMap;
}

void TranslationBlock::addMap(QString source, QString translation)
{
    m_translationMap.insert(source, translation);
}

void TranslationBlock::clear()
{
    m_className = "";
    m_translationMap.clear();
}
