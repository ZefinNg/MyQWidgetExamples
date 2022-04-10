#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QThread>
#include <QString>
#include "Factory.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onBtnDirectClicked();
    void onBtnQueuedClicked();
    void onBtnBlockClicked();
    void onBtnUniqueClicked();

    void onProduct();

private:
    QPushButton *m_btnDirectConnect;
    QPushButton *m_btnQueuedConnect;
    QPushButton *m_btnBlockConnect;
    QPushButton *m_btnUniqueConnect;

    Qt::HANDLE m_mainThreadId;

    QThread *m_factoryThread;
    Factory *m_factory;
    Qt::ConnectionType m_connectType;
};
#endif // WIDGET_H
