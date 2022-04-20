#ifndef TXTEXCELHANDLER_H
#define TXTEXCELHANDLER_H

#include <QObject>
#include <QMap>
#include <QFileInfo>
#include "../Utils/ExcelReadWriterQtXlsx/ExcelRW.h"

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

    bool setOutputExcelFile(const QString &filePath);
    bool writeCell(const QString text, const int row, const int column,
                   QXlsx::Format format = QXlsx::Format());

signals:

private:
    QString m_filePath;
    XLSX::ExcelRW *m_excelRW;
};

#endif // TXTEXCELHANDLER_H
