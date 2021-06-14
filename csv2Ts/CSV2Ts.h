#ifndef CSV2TS_H
#define CSV2TS_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QList>
#include <QMap>
#include <QCoreApplication>
#include <QDateTime>
#include "Domains/TranslationBlock.h"

#include <QDebug>

class CSV2Ts : public QObject
{
    Q_OBJECT
public:
    explicit CSV2Ts(QObject *parent = 0);

    bool readFile(QString filePath);

    QList<TranslationBlock> classTranslationList() const;

    QString findTranslation(QString className, QString source);

signals:

public slots:

private:
    void dealEachLine(QString eachLine);
    void write2File(QString eachLine);

private:
    QFile *m_file;
    QList<TranslationBlock> m_classTranslationList;
    TranslationBlock m_translationBlock;
    QFile *m_needDealFile;
};

#endif // CSV2TS_H
