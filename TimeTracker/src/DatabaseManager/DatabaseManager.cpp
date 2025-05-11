#include "DatabaseManager.h"
#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QMutex DatabaseManager::s_mutex;
DatabaseManager* DatabaseManager::s_instance = nullptr;

DatabaseManager *DatabaseManager::getInstance()
{
    if (s_instance == nullptr) {
        QMutexLocker locker(&s_mutex);
        if (s_instance == nullptr)
            s_instance = new DatabaseManager();
    }

    return s_instance;
}

DatabaseManager::~DatabaseManager()
{
    if (m_database.isOpen())
        m_database.close();
}

bool DatabaseManager::updateApplicationInfo(const ApplicationInfo &appInfo) 
{
    if (!m_appInfoMap.contains(appInfo.appName().toStdString())) {
        return this->insertAppInfoToDb(appInfo);
    }
    else {
        return this->updateAppInfoToDb(appInfo);
    }
}

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("tracker.db");
    if (!m_database.open()) {
        qDebug() << "Failed to open .db file.";
        return;
    }

    this->initSqlTable();
    this->refreshAppInfoData();
}

void DatabaseManager::initSqlTable()
{
    QSqlQuery query(m_database);
    QString sqlCmd = QStringLiteral("CREATE TABLE IF NOT EXISTS app_usage_stats ("
                                    "app_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "app_name TEXT NOT NULL,"
                                    "app_path TEXT NOT NULL,"
                                    "first_launch_time INTEGER NOT NULL,"
                                    "last_launch_time INTEGER NOT NULL,"
                                    "total_running_time INTEGER DEFAULT 0,"
                                    "remark_info TEXT"
                                    ");");
    if (query.prepare(sqlCmd)) {
        if (!query.exec()) {
            qDebug() << "Failed to exec sql. Error: " << query.lastError().text();
        }
        else {
            // 创建索引
            query.exec("CREATE INDEX IF NOT EXISTS idx_app_name ON app_usage_stats(app_name)");
            query.exec("CREATE INDEX IF NOT EXISTS idx_last_launch ON app_usage_stats(last_launch_time)");
        }
    }
    else {
        qDebug() << "Failed to prepare sql. Error: " << query.lastError().text();
    }
}

void DatabaseManager::refreshAppInfoData()
{
    QString sqlCmd = QStringLiteral("SELECT * FROM app_usage_stats;");
    QSqlQuery query(m_database);

    if (query.prepare(sqlCmd)) {
        if (query.exec()) {
            while (query.next()) {
                ApplicationInfo appInfo;
                appInfo.setId(query.value(0).toInt());
                appInfo.setAppName(query.value(1).toString());
                appInfo.setAppPath(query.value(2).toString());
                appInfo.setFirstLaunchTime(query.value(3).toInt());
                appInfo.setLastLaunchTime(query.value(4).toInt());
                appInfo.setTotalRunningTime(query.value(5).toInt());
                appInfo.setRemarkInfo(query.value(5).toString());

                m_appInfoMap.insert(appInfo.appName().toStdString(), appInfo);
            }
        }
        else {
            qDebug() << "Failed to exec sql. Error: " << query.lastError().text();
        }
    }
    else {
        qDebug() << "Failed to prepare sql. Error: " << query.lastError().text();
    }
}

QMap<std::string, ApplicationInfo> *DatabaseManager::appInfoMap()
{
    return &m_appInfoMap;
}

bool DatabaseManager::insertAppInfoToDb(const ApplicationInfo &appInfo)
{
    QString sqlCmd = QStringLiteral("INSERT INTO app_usage_stats "
                                    "(app_name, app_path, first_launch_time, last_launch_time, total_running_time, remark_info)"
                                    "VALUES "
                                    "('%1', '%2', %3, %4, %5, '%6');")
                         .arg(appInfo.appName())
                         .arg(appInfo.appPath())
                         .arg(appInfo.firstLaunchTime())
                         .arg(appInfo.lastLaunchTime())
                         .arg(appInfo.totalRunningTime())
                         .arg(appInfo.remarkInfo());

    QSqlQuery query(m_database);

    if (!query.prepare(sqlCmd)) {
        qDebug() << "Failed to prepare sql. Error: " << query.lastError().text();
        return false;
    }

    m_database.transaction();
    if (!query.exec()) {
        qDebug() << "Failed to exec sql. Error: " << query.lastError().text();
        m_database.rollback();
        return false;
    }
    m_database.commit();

    m_appInfoMap.insert(appInfo.appName().toStdString(), appInfo);

    return true;
}

bool DatabaseManager::updateAppInfoToDb(const ApplicationInfo &appInfo)
{
    QString sqlCmd = QStringLiteral("UPDATE app_usage_stats "
                                    "SET last_launch_time = %1, total_running_time = %2 "
                                    "WHERE app_name = '%3';")
                         .arg(appInfo.lastLaunchTime())
                         .arg(appInfo.totalRunningTime())
                         .arg(appInfo.appName());

    QSqlQuery query(m_database);

    if (!query.prepare(sqlCmd)) {
        qDebug() << "Failed to prepare sql. Error: " << query.lastError().text();
        return false;
    }

    m_database.transaction();
    if (!query.exec()) {
        qDebug() << "Failed to exec sql. Error: " << query.lastError().text();
        m_database.rollback();
        return false;
    }
    m_database.commit();

    m_appInfoMap.insert(appInfo.appName().toStdString(), appInfo);

    return true;
}
