#include "TranslationBlock.h"

TranslationBlock::TranslationBlock()
    : m_className(),
      m_translationMap()
{

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

bool TranslationBlock::addMap(QString source, QString translation)
{
    if (m_translationMap.contains(source))
        return false;

    m_translationMap.insert(source, translation);
    return true;
}

void TranslationBlock::clear()
{
    m_className = "";
    m_translationMap.clear();
}
