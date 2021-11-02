#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QObject>
#include <QMap>
#include <QFileInfo>
#include "../Utils/ExcelReadWriter/ExcelReadWriter.h"
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
        THREE_COLUMNS,   //class, src, translation
        FIVE_COLUMNS     //errorNum, TipsSrc, InfoSrc, TipsTranslation, InfoTranslation
    };

    explicit TsExcelHandler(QObject *parent = nullptr);

    void setFilePath(QString filePath);
    void closeFile();

    TsExcelHandler::HANDLE_ERROR handleTranslation();

    bool setOutputExcelFile(const QString filePath);
    bool writeCell(const QString text, const int row, const int column);

    QString getTranslation(const QString field, const QString srcText);
    QString getTranslation(const QString srcText);
    QStringList getTipsAndInfo(const QString num);

    TsExcelHandler::FILE_FORMAT getFileFormat() const;
    void setFileFormat(const TsExcelHandler::FILE_FORMAT &fileFormat);

private:
    int blockListIndexOf(const QString className);

private:
    QString         m_filePath;
    ExcelReadWrite *m_excelRW;
    FILE_FORMAT     m_fileFormat;

    QList<TranslationBlock> m_translationBlockList;
    TranslationBlock m_translationBlock;
};

#endif // EXCELHANDLER_H
