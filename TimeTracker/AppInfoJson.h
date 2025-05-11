#ifndef APPINFOJSON_H
#define APPINFOJSON_H

#include <QObject>
#include <QMutex>
#include <QJsonDocument>

class AppInfoJson : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString jsonPath READ jsonPath WRITE setJsonPath NOTIFY jsonPathChanged FINAL)

    AppInfoJson* getInstance();
    ~AppInfoJson();

    QString jsonPath() const;
    void setJsonPath(const QString &newJsonPath);

signals:
    void jsonPathChanged();

private:
    explicit AppInfoJson(QObject *parent = nullptr);

private:
    static AppInfoJson* s_instance;
    static QMutex s_mutex;

    QString m_jsonPath;
};

#endif // APPINFOJSON_H
