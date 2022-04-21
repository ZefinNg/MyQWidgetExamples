#ifndef SOURCEFILEHANDLER_H
#define SOURCEFILEHANDLER_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QtXml>
#include <QSettings>
#include "../Utils/ExcelReadWriterQtXlsx/ExcelRW.h"

class SourceFileHandler : public QObject
{
    Q_OBJECT
public:
    enum FILE_TYPE {
        TS_FILE = 0,
        TXT_FILE,
        INI_FILE,
        XML_FILE
    };

    explicit SourceFileHandler(QObject *parent = nullptr);
    ~SourceFileHandler();

    void setSrcFilePath(const QString filePath, const FILE_TYPE fileType = TS_FILE);

    bool conver2Excel(const QString outputFilePath);

signals:

private:
    bool ts2Excel(const int &columns = 2);
    bool txt2Excel();
    bool ini2Excel();
    bool xml2Excel();

private:
    QString m_srcFilePath;
    FILE_TYPE m_srcFileType;
    QString m_outputFilePath;

    XLSX::ExcelRW *m_excelRW;
};

#endif // SOURCEFILEHANDLER_H
