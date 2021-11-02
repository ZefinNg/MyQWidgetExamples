#ifndef TSFIXUP_H
#define TSFIXUP_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtXml>
#include "../ExcelHandler/TsExcelTHandler.h"

#include <QDebug>

class TsFixUp : public QObject
{
    Q_OBJECT
public:
    explicit TsFixUp(QObject *parent = 0);
    ~TsFixUp();

    TsExcelHandler::HANDLE_ERROR setTranstlationFile(const QString xlsxPath);
    void closeExcelFile();

    bool setTsFile(const QString filePath);
    void setOutputTsFile(const QString outputFile);

    bool excel2Ts();

signals:

public slots:

private:
    void createNewTsFile(QString filePath);

private:
    QString m_fileName;
    QString m_outputFile;

    QFile *m_tsFile;
    QFile *m_outputTsFile;

    QDomDocument *m_domDoc;

    TsExcelHandler *m_excelHandler;
};

#endif // TSFIXUP_H
