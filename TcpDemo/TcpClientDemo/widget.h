#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onRead();

    void on_btnConnect_clicked();

    void on_btnSend_clicked();

    void onSendTimeout();

private:
    Ui::Widget *ui;

    QTcpSocket *m_tcpSocket;
    QTimer m_sendTimer;
    QTimer m_timeOutTimer;
    int m_frameId;
    int m_hasSendTimes;
};

#endif // WIDGET_H
