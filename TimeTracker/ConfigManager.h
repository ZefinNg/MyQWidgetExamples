#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QMutex>
#include "ApplicationInfo.h"

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    static ConfigManager* getInstance();
    void setConfigFile(const QString& filePath);

    void readConfigFile();
    void writeConfigFile();

signals:

public slots:

private:

private:
    explicit ConfigManager(QObject *parent = 0);
    static QMutex s_mutex;
    static ConfigManager *s_instance;

    QSettings *m_configSettings;
};

#endif // CONFIGMANAGER_H
