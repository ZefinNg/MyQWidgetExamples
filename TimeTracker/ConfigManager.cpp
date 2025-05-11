#include "ConfigManager.h"
#include <QMutexLocker>
#include <QMutexLocker>

QMutex ConfigManager::s_mutex;
ConfigManager *ConfigManager::s_instance = nullptr;

ConfigManager *ConfigManager::getInstance()
{
    if (s_instance == nullptr) {
        QMutexLocker locker(&ConfigManager::s_mutex);
        if (s_instance == nullptr) {
            s_instance = new ConfigManager();
        }
    }

    return s_instance;
}

void ConfigManager::setConfigFile(const QString &filePath)
{
    if (m_configSettings != nullptr) {
        m_configSettings->endGroup();
        delete m_configSettings;
    }

    m_configSettings = new QSettings(filePath, QSettings::IniFormat, this);
}

ConfigManager::ConfigManager(QObject *parent)
    : QObject(parent),
      m_configSettings(nullptr)
{
}

void ConfigManager::readConfigFile()
{

}

void ConfigManager::writeConfigFile()
{

}
