#ifndef EXCELREADWRITE_H
#define EXCELREADWRITE_H

#include <QObject>
#include <QAxObject>

class ExcelReadWrite : public QObject
{
    Q_OBJECT
public:
    explicit ExcelReadWrite(QString filePath, QObject *parent = nullptr);
    ~ExcelReadWrite();

    QString title();

    int getWorkSheetCount();

    void setCurrentWorkSheet(int index);

    int getRows();
    int getColumns();

    void closeFile();

    QString getCellText(int row, int col);

signals:

private:

private:
    QAxObject *m_excelApp;
    QAxObject *m_workbooks;
    QAxObject *m_fileWorkbook;
    QAxObject *m_workSheets;
};

#endif // EXCELREADWRITE_H
