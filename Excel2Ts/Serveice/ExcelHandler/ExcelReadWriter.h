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
    enum ALIGNMENT_H {
        ALIGN_LEFT   = -4131,
        ALIGN_RIGHT  = -4152,
        ALIGN_CENTER = -4108
    };

    enum ALIGNMENT_V {
        ALIGN_TOP    = -4160,
        ALIGN_BOTTOM = -4107
    };

    explicit ExcelReadWrite(QObject *parent = nullptr);
    ~ExcelReadWrite();

    bool isOpen();
    bool openFile(QString filePath);

    QString getTitle();
    //TODO:无法正常设置成功
    bool setTitle(QString title);

    QString getWorksheetName();
    bool setWorksheetName(QString worksheetName);

    int getWorksheetCount();
    bool setCurrentWorkSheet(int index);

    void appendWorksheet();
    //TODO:当工作表有数据时，无法删除
    void deleteCurrentWorksheet();

    int getRows();
    int getColumns();

    int getStartRows();
    int getStartColumns();

    QString getCellText(int row, int col);
    bool    setCellText(QString text, int row, int col,
                        ALIGNMENT_H alignmentH = ALIGN_LEFT,
                        ALIGNMENT_V alignmentV = ALIGN_TOP,
                        bool wrap = false);

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
