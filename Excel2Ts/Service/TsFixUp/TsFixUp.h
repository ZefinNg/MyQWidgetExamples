#ifndef TSFIXUP_H
#define TSFIXUP_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtXml>
#include "../ExcelHandler/ExcelHandler.h"

#include <QDebug>

class TsFixUp : public QObject
{
    Q_OBJECT
public:
    explicit TsFixUp(QObject *parent = 0);

    ExcelHandler::HANDLE_ERROR setExcelFile(const QString filePath);
    void closeExcelFile();

    bool setTsFile(const QString filePath);
    void setOutputTsFile(const QString outputFile);

    bool fixUpTsFile();

signals:

public slots:

private:
    void createNewTsFile(QString filePath);

private:
    QString m_fileName;
    QString m_outputFile;

    QFile *m_tsFile;
    QFile *m_outputTsFile;

    ExcelHandler *m_excelHandler;
};

#endif // TSFIXUP_H
