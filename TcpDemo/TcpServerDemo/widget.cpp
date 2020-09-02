#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");
    m_tcpServer = new QTcpServer(this);
    m_tcpSocket = new QTcpSocket(this);

    if (!m_tcpServer->listen(QHostAddress::Any, 1234)) {
        qDebug() << m_tcpServer->errorString();
    }

    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onNewConnection()
{
    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onReceiveData()));
}

void Widget::onReceiveData()
{
    QByteArray buffer;
    buffer = m_tcpSocket->readAll();
//    qDebug() << QString::fromLatin1(buffer);
    ui->textBrowser->append(QString::fromLatin1(buffer));
    m_tcpSocket->write(buffer);
}
