#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(onRead()));

    m_sendTimer.setInterval(2000);
    connect(&m_sendTimer, SIGNAL(timeout()), this, SLOT(on_btnSend_clicked()));

    m_timeOutTimer.setInterval(500);
    connect(&m_timeOutTimer, SIGNAL(timeout()), this, SLOT(onSendTimeout()));
    m_frameId = 0;
    m_hasSendTimes = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onRead()
{
    m_timeOutTimer.stop();
    QByteArray buffer = m_tcpSocket->readAll();
    QString receiveData = QString::fromLatin1(buffer);
    if (receiveData == QString::number(m_frameId)) {
        m_frameId++;
        m_hasSendTimes = 0;
    }
}

void Widget::on_btnConnect_clicked()
{
    m_tcpSocket->connectToHost(ui->lineEditIPAddress->text(), 1234);
    m_sendTimer.start();
}

void Widget::on_btnSend_clicked()
{
#if 0
    m_tcpSocket->write(ui->lineEditContext->text().toLatin1());
    m_tcpSocket->flush();
#else
    QString dataToSend = QString::number(m_frameId);
    m_tcpSocket->write(dataToSend.toLatin1());
    ui->textBrowser->append(QString::number(m_frameId));
    m_timeOutTimer.start();
#endif
}

void Widget::onSendTimeout()
{
    QString dataToSend = QString::number(m_frameId);
    m_tcpSocket->write(dataToSend.toLatin1());
    ui->textBrowser->append(QString::number(m_frameId));
}
