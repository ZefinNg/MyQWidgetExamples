#include "TranslationBlock.h"

TranslationBlock::TranslationBlock()
    : m_field(),
      m_translationMap()
{

}

QString TranslationBlock::field() const
{
    return m_field;
}

void TranslationBlock::setField(const QString &field)
{
    m_field = field;
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
    m_field = "";
    m_translationMap.clear();
}
