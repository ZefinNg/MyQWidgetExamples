#ifndef ERRORTXTFIXUP_H
#define ERRORTXTFIXUP_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class ErrorTxtFixUp : public QObject
{
    Q_OBJECT
public:
    explicit ErrorTxtFixUp(QObject *parent = nullptr);
    ~ErrorTxtFixUp();

    bool openFile(const QString &filePath);
    bool fixUpFile();

    void setOutputFile(const QString &newFilePath);

signals:

private:
    QString getNum(const QString &text);

private:
    QFile      *m_file;
    QString     m_filePath;
    QStringList m_contextList;
};

#endif // ERRORTXTFIXUP_H
