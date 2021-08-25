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
    QString getWorkSheetName();

    int getWorkSheetCount();

    bool setCurrentWorkSheet(int index);

    int getRows();
    int getColumns();

    void closeFile();

    QString getCellText(int row, int col);

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
};

#endif // EXCELREADWRITE_H
