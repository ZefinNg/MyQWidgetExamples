#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QMutex>
#include <QSqlDatabase>
#include <QMap>
#include "ApplicationInfo.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager* getInstance();
    ~DatabaseManager();

    bool updateApplicationInfo(const ApplicationInfo& appInfo);

    QMap<std::string, ApplicationInfo>* appInfoMap();

    bool insertAppInfoToDb(const ApplicationInfo& appInfo);
    bool updateAppInfoToDb(const ApplicationInfo& appInfo);

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    void initSqlTable();
    void refreshAppInfoData();

private:
    static QMutex s_mutex;
    static DatabaseManager* s_instance;

    QSqlDatabase m_database;
    QMap<std::string, ApplicationInfo> m_appInfoMap;
};

#endif // DATABASEMANAGER_H
