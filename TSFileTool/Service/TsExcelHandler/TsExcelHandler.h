﻿#ifndef TSEXCELHANDLER_H
#define TSEXCELHANDLER_H

#include <QObject>
#include <QFileInfo>
//#include "../Utils/ExcelReadWriterAxObject/ExcelReadWriter.h"
#include "../Utils/ExcelReadWriterQtXlsx/ExcelRW.h"
#include "TranslationBlock.h"

class TsExcelHandler : public QObject
{
    Q_OBJECT
public:
    enum HANDLE_ERROR {
        NORMAL = 0,
        OPEN_FILE_FAILED,
        FORMAT_ERROR,
        REPEAT_KEY
    };

    enum FILE_FORMAT {
        TWO_COLUMNS = 2, //src, translation
        THREE_COLUMNS    //class, src, translation
    };

    explicit TsExcelHandler(QObject *parent = nullptr);

    void setFilePath(QString filePath);
    void closeFile();

    TsExcelHandler::HANDLE_ERROR handleTranslation();

    bool setOutputExcelFile(const QString filePath);
    bool writeCell(const QString text, const int row, const int column,
                   QXlsx::Format format = QXlsx::Format());

    QString getTranslation(const QString field, const QString srcText);
    QString getTranslation(const QString srcText);

    TsExcelHandler::FILE_FORMAT getFileFormat() const;
    void setFileFormat(const TsExcelHandler::FILE_FORMAT &fileFormat);

    bool mergeCells(const int firstRow, const int firstColumn,
                    const int lastRow, const int lastColumn);

private:
    int blockListIndexOf(const QString className);

private:
    QString         m_filePath;
//    AXOBJECT::ExcelReadWrite *m_excelRW;
    XLSX::ExcelRW *m_excelRW;
    FILE_FORMAT     m_fileFormat;

    QList<TranslationBlock> m_translationBlockList;
    TranslationBlock m_translationBlock;
};

#endif // TSEXCELHANDLER_H
