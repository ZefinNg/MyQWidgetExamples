#ifndef TRANSLATIONBLOCK_H
#define TRANSLATIONBLOCK_H

#include <QString>
#include <QList>
#include <QMap>

class TranslationBlock
{
public:
    TranslationBlock();

    QString className() const;
    void setClassName(const QString &className);

    QMap<QString, QString> translationMap() const;
    void setTranslationMap(const QMap<QString, QString> &translationMap);

    void addMap(QString source, QString value);
    void clear();

private:
    QString m_className;
    QMap<QString, QString> m_translationMap;
};

#endif // TRANSLATIONBLOCK_H
