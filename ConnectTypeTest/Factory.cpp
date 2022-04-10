#include "Factory.h"
#include <unistd.h>
#include <QThread>
#include <QDebug>

Factory::Factory(QObject *parent) : QObject(parent)
{

}

void Factory::doWork()
{
    m_isRunning = true;
    m_threadId = QThread::currentThreadId();
    qDebug() << __FUNCTION__ << "子线程:" << m_threadId;

    while (m_isRunning) {
        sleep(1);
        emit product();
    }
}

void Factory::stopWork()
{
    m_isRunning = false;
}

void Factory::onBtnDirectionClicked()
{
    qDebug() << __FUNCTION__ << "线程:" << QThread::currentThreadId();
}

Qt::HANDLE Factory::threadId() const
{
    return m_threadId;
}
