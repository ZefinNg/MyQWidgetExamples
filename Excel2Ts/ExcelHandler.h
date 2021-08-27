#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include "ExcelReadWriter.h"

class ExcelHandler : public QObject
{
    Q_OBJECT
public:
    enum EXCEL_HANDLE_ERROR {
        OPEN_FILE_FAILED = 0,
    };

    explicit ExcelHandler(QObject *parent = nullptr);

    EXCEL_HANDLE_ERROR handleFile(QString filePath);

signals:

private:
    ExcelReadWrite *m_excelRW;
};

#endif // EXCELHANDLER_H
