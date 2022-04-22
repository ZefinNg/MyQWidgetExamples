#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QObject>
#include <QString>
#include "../Utils/ExcelReadWriterQtXlsx/ExcelRW.h"

class ExcelHandler : public QObject
{
    Q_OBJECT
public:
    enum FILE_TYPE {
        TS_FILE = 0,
        TXT_FILE,
        INI_FILE,
        XML_FILE
    };

    explicit ExcelHandler(QObject *parent = nullptr);
    ~ExcelHandler();

    void setFilePath(const QString& filePath);

    bool conver2File(const FILE_TYPE& fileType, const QString &outputFilePath);

signals:

private:
    bool excel2Ts();
    bool excel2Txt();
    bool excel2Ini();
    bool excel2Xml();

private:
    QString m_excelFilePath;
    QString m_outputFilePath;

    XLSX::ExcelRW *m_excelRW;
};

#endif // EXCELHANDLER_H
