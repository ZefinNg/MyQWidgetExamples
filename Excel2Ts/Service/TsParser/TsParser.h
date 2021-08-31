#ifndef TSPARSER_H
#define TSPARSER_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtXml>
#include "CSV2Ts.h"

#include <QDebug>

class TsParser : public QObject
{
    Q_OBJECT
public:
    explicit TsParser(QObject *parent = 0);

    void setFilePath(QString filePath);

signals:

public slots:

private:
    void createNewTsFile(QString filePath);

private:
    QString m_fileName;
    QFile *m_tsFile;
    CSV2Ts *m_csv2Ts;
    QList<TranslationBlock> m_translationList;
    QFile *m_newTsFile;
};

#endif // TSPARSER_H
