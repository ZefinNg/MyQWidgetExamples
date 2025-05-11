#include "ApplicationInfo.h"

ApplicationInfo::ApplicationInfo() :
    m_id(-1),
    m_appName(""),
    m_appPath(""),
    m_firstLaunchTime(-1),
    m_lastLaunchTime(-1),
    m_totalRunningTime(-1),
    m_remarkInfo(""),
    m_isActiveFirstTime(true)
{
}

ApplicationInfo::~ApplicationInfo()
{

}

QString ApplicationInfo::appName() const
{
    return m_appName;
}

void ApplicationInfo::setAppName(const QString &appName)
{
    if (appName != m_appName)
        m_appName = appName;
}

QString ApplicationInfo::appPath() const
{
    return m_appPath;
}

void ApplicationInfo::setAppPath(const QString &appPath)
{
    if (appPath != m_appPath)
        m_appPath = appPath;
}

int ApplicationInfo::totalRunningTime() const
{
    return m_totalRunningTime;
}

void ApplicationInfo::setTotalRunningTime(const int &runningTime)
{
    if (runningTime != m_totalRunningTime)
        m_totalRunningTime = runningTime;
}

QString ApplicationInfo::remarkInfo() const
{
    return m_remarkInfo;
}

void ApplicationInfo::setRemarkInfo(const QString &newRemarkInfo)
{
    m_remarkInfo = newRemarkInfo;
}

int ApplicationInfo::id() const
{
    return m_id;
}

void ApplicationInfo::setId(int newId)
{
    m_id = newId;
}

int ApplicationInfo::lastLaunchTime() const
{
    return m_lastLaunchTime;
}

void ApplicationInfo::setLastLaunchTime(int newLastLaunchTime)
{
    m_lastLaunchTime = newLastLaunchTime;
}

bool ApplicationInfo::isActiveFirstTime() const
{
    return m_isActiveFirstTime;
}

void ApplicationInfo::setIsActiveFirstTime(bool newIsActiveFirstTime)
{
    m_isActiveFirstTime = newIsActiveFirstTime;
}

int ApplicationInfo::firstLaunchTime() const
{
    return m_firstLaunchTime;
}

void ApplicationInfo::setFirstLaunchTime(int newFirstLaunchTime)
{
    m_firstLaunchTime = newFirstLaunchTime;
}
