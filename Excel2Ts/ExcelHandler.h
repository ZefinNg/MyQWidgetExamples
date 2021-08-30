#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QThread>
#include <QMap>
#include "ExcelReadWriter.h"

class ExcelHandler : public QThread
{
    Q_OBJECT
public:
    enum HANDLE_ERROR {
        OPEN_FILE_FAILED = 0,
        FORMAT_ERROR,
        REPEAT_KEY
    };

    explicit ExcelHandler(QObject *parent = nullptr);

    void setFilePath(QString filePath);

    /* 注意判断Mapper是否为空
     * key为源文，value为译文
     */
    QMap<QString, QString>getTranslationMapper();

signals:
    void errorOccur(ExcelHandler::HANDLE_ERROR);

protected:
    void run();

private:
    QString m_filePath;
    ExcelReadWrite *m_excelRW;
    QMap<QString, QString> m_translationMapper;
};

#endif // EXCELHANDLER_H
