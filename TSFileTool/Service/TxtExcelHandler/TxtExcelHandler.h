#ifndef TXTEXCELHANDLER_H
#define TXTEXCELHANDLER_H

#include <QObject>
#include <QMap>
#include <QFileInfo>
#include "../Utils/ExcelReadWriterQtXlsx/ExcelReadWriter.h"

class TxtExcelHandler : public QObject
{
    Q_OBJECT
public:
    enum FILE_FORMAT {
        FILE_TXT = 0,
        FILE_INI,
        FILE_XML
    };

    explicit TxtExcelHandler(QObject *parent = nullptr);
    ~TxtExcelHandler();

    void setFilePath(const QString &filePath);
    void closeFile();

signals:

private:
    QString m_filePath;
    XLSX::ExcelReadWriter *m_excelRW;
};

#endif // TXTEXCELHANDLER_H
