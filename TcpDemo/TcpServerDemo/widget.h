#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

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
    void onNewConnection();
    void onReceiveData();

private:
    Ui::Widget *ui;
    QTcpServer *m_tcpServer;
    QTcpSocket *m_tcpSocket;
};

#endif // WIDGET_H
