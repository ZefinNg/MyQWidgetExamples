#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QString>
#include <QDateTime>

class ApplicationInfo
{
public:
    ApplicationInfo();
    ~ApplicationInfo();

    QString appName() const;
    void setAppName(const QString &appName);

    QString appPath() const;
    void setAppPath(const QString &appPath);

    int firstLaunchTime() const;
    void setFirstLaunchTime(int newFirstLaunchTime);

    int totalRunningTime() const;
    void setTotalRunningTime(const int &runningTime);

    QString remarkInfo() const;
    void setRemarkInfo(const QString &newRemarkInfo);

    int id() const;
    void setId(int newId);

    int lastLaunchTime() const;
    void setLastLaunchTime(int newLastLaunchTime);

    bool isActiveFirstTime() const;
    void setIsActiveFirstTime(bool newIsActiveFirstTime);

private:
    int m_id;
    QString m_appName;
    QString m_appPath;
    int m_firstLaunchTime;
    int m_lastLaunchTime;
    int m_totalRunningTime;
    QString m_remarkInfo;
    bool m_isActiveFirstTime;
};

#endif // APPLICATIONINFO_H
