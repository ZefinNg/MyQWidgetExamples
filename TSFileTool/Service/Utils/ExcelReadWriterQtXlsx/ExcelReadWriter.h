#ifndef EXCELREADWRITER_H
#define EXCELREADWRITER_H

#include <QObject>
#include "xlsxdocument.h"

namespace XLSX {

class ExcelReadWriter : public QObject
{
    Q_OBJECT
public:
    explicit ExcelReadWriter(QObject *parent = nullptr);
    ~ExcelReadWriter();

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
    bool setCellText(const int row, const int col, const QString text, const QXlsx::Format format);

    bool save();
    bool saveAs(const QString& filePath);

    QString getFilePath() const;

signals:

private:
    QString m_filePath;
    QXlsx::Document *m_xlsx;
};

}

#endif // EXCELREADWRITER_H
