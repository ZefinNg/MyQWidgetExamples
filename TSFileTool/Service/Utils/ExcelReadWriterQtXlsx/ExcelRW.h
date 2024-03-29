#ifndef EXCELRW_H
#define EXCELRW_H

#include <QObject>
#include "xlsxdocument.h"

namespace XLSX {

class ExcelRW : public QObject
{
    Q_OBJECT
public:
    explicit ExcelRW(QObject *parent = nullptr);
    ~ExcelRW();

    bool openFile(const QString& filePath);

    QString getTitle() const;
    bool setTitle(const QString& title);

    QStringList getWorksheetNames() const;
    bool selectWorksheet(const QString& name);

    QString getWorkSheetName() const;
    bool setWorksheetName(const QString& newName);

    bool addWorksheet(const QString &name = "");
    bool deleteWorksheet(const QString& name);

    int getRowCount() const;
    int getColumnCount() const;

    int getFirstRow() const;
    int getFirstColumn() const;

    QVariant getCellText(const int row, const int col) const;
    bool setCellText(const int row, const int col, const QString text, const QXlsx::Format format = QXlsx::Format());

    bool mergeCells(const int firstRow, const int firstColumn,
                     const int lastRow,  const int lastColumn);

    bool save();
    bool saveAs(const QString& filePath);

    QString getFilePath() const;

signals:

private:
    QString m_filePath;
    QXlsx::Document *m_xlsx;
};

}

#endif // EXCELRW_H
