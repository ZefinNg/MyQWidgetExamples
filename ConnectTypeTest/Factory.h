#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>

class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(QObject *parent = nullptr);

    Qt::HANDLE threadId() const;

public slots:
    void doWork();

signals:

private:
    bool m_isRunning;
    Qt::HANDLE m_threadId;
};

#endif // FACTORY_H
