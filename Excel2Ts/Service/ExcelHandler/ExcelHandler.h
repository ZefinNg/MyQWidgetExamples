#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QObject>
#include <QMap>
#include "../Utils/ExcelReadWriter/ExcelReadWriter.h"
#include "TranslationBlock.h"

class ExcelHandler : public QObject
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

    explicit ExcelHandler(QObject *parent = nullptr);

    void setFilePath(QString filePath);

    ExcelHandler::HANDLE_ERROR handleFile();

    QString getTranslation(const QString className, const QString srcText);
    QString getTranslation(const QString srcText);

    ExcelHandler::FILE_FORMAT getFileFormat() const;
    void setFileFormat(const ExcelHandler::FILE_FORMAT &fileFormat);

private:
    int blockListIndexOf(const QString className);

private:
    QString m_filePath;
    ExcelReadWrite *m_excelRW;
    FILE_FORMAT m_fileFormat;

    QList<TranslationBlock> m_translationBlockList;
    TranslationBlock m_translationBlock;
};

#endif // EXCELHANDLER_H
