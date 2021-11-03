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

    bool setTsFile(const QString& filePath);
    void setOutputTsFilePath(const QString& outputFile);

    void setOutputXlsxFilePath(const QString& outputFile);

    bool excel2Ts();
    bool ts2Excel();

signals:

public slots:

private:
    void createNewTsFile(const QString& filePath);

private:
    QString m_tsSourceFilePath;
    QString m_tsOutputFilePath;

    QString m_xlsxOutputFilePath;

    QFile *m_tsSourceFile;
    QFile *m_outputTsFile;

    QDomDocument *m_domDoc;

    TsExcelHandler *m_excelHandler;
};

#endif // TSFIXUP_H
