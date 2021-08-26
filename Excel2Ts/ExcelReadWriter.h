#ifndef EXCELREADWRITE_H
#define EXCELREADWRITE_H

#include <QObject>
#include <QAxObject>
#include <QFile>
#include <ole2.h>

class ExcelReadWrite : public QObject
{
    Q_OBJECT
public:
    explicit ExcelReadWrite(QObject *parent = nullptr);
    ~ExcelReadWrite();

    bool isOpen();
    bool openFile(QString filePath);

    QString title();
    QString getWorksheetName();

    int getWorksheetCount();

    bool setCurrentWorkSheet(int index);

    int getRows();
    int getColumns();

    int getStartRows();
    int getStartColumns();

    QString getCellText(int row, int col);

    void closeFile();

signals:

private:

private:
    bool      m_isOpen;
    QString   m_filePath;

    QAxObject *m_excelApp;
    QAxObject *m_workbooks;
    QAxObject *m_fileWorkbook;
    QAxObject *m_worksheets;
    QAxObject *m_currentWorksheet;
    QAxObject *m_usedRange;
    QAxObject *m_rows;
    QAxObject *m_columns;
};

#endif // EXCELREADWRITE_H
