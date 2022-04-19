#ifndef TRANSLATIONBLOCK_H
#define TRANSLATIONBLOCK_H

#include <QString>
#include <QList>
#include <QMap>

class TranslationBlock
{
public:
    TranslationBlock();

    QString field() const;
    void setField(const QString &field);

    QMap<QString, QString> translationMap() const;
    void setTranslationMap(const QMap<QString, QString> &translationMap);

    bool addMap(QString source, QString value);
    void clear();

private:
    QString m_field;
    QMap<QString, QString> m_translationMap;
};

#endif // TRANSLATIONBLOCK_H
