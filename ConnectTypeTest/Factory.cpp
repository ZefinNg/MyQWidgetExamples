#include "Factory.h"
#include <unistd.h>
#include <QThread>

Factory::Factory(QObject *parent) : QObject(parent)
{

}

void Factory::doWork()
{
    m_isRunning = true;
    m_threadId = QThread::currentThreadId();

    while (m_isRunning) {
        usleep(500 * 1000);
    }

}

Qt::HANDLE Factory::threadId() const
{
    return m_threadId;
}
