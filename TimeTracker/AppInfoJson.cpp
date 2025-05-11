#include "AppInfoJson.h"
#include <QMutexLocker>

AppInfoJson *AppInfoJson::s_instance = nullptr;
QMutex AppInfoJson::s_mutex;

AppInfoJson *AppInfoJson::getInstance()
{
    if (s_instance == nullptr) {
        QMutexLocker locker(&s_mutex);
        if (s_instance == nullptr)
            s_instance = new AppInfoJson();
    }

    return s_instance;
}

AppInfoJson::~AppInfoJson()
{

}

AppInfoJson::AppInfoJson(QObject *parent)
    : QObject{parent}
{}

QString AppInfoJson::jsonPath() const
{
    return m_jsonPath;
}

void AppInfoJson::setJsonPath(const QString &newJsonPath)
{
    if (m_jsonPath == newJsonPath)
        return;
    m_jsonPath = newJsonPath;
    emit jsonPathChanged();
}
