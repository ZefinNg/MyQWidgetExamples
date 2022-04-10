#include "Widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_btnDirectConnect(new QPushButton("Direct", this)),
      m_btnQueuedConnect(new QPushButton("Queued", this)),
      m_btnBlockConnect(new QPushButton("Block", this)),
      m_btnUniqueConnect(new QPushButton("Unique", this)),
      m_factoryThread(new QThread()),
      m_factory(new Factory())
{
    QHBoxLayout *btnHorizonalLayout = new QHBoxLayout(this);
    btnHorizonalLayout->addWidget(m_btnDirectConnect);
    btnHorizonalLayout->addWidget(m_btnQueuedConnect);
    btnHorizonalLayout->addWidget(m_btnBlockConnect);
    btnHorizonalLayout->addWidget(m_btnUniqueConnect);

    m_factory->moveToThread(m_factoryThread);
    connect(m_factoryThread, SIGNAL(started()), m_factory, SLOT(doWork()));
    connect(m_factoryThread, SIGNAL(finished()), m_factory, SLOT(deleteLater()));
    connect(m_factoryThread, SIGNAL(finished()), m_factoryThread, SLOT(deleteLater()));
    m_factoryThread->start();

    connect(m_btnDirectConnect, SIGNAL(clicked()), this, SLOT(onBtnDirectClicked()));
    connect(m_btnQueuedConnect, SIGNAL(clicked()), this, SLOT(onBtnQueuedClicked()));
    connect(m_btnBlockConnect,  SIGNAL(clicked()), this, SLOT(onBtnBlockClicked()));
    connect(m_btnUniqueConnect, SIGNAL(clicked()), this, SLOT(onBtnUniqueClicked()));

    m_mainThreadId = QThread::currentThreadId();
    qDebug() << "主线程:" << m_mainThreadId;
}

Widget::~Widget()
{
    m_factoryThread->quit();
    m_factoryThread->wait(200);

    m_factoryThread = nullptr;
    m_factory = nullptr;
}

void Widget::onBtnDirectClicked()
{
    disconnect(this, 0, 0, 0);
    connect(m_factory, SIGNAL(product()), this, SLOT(onProduct()), Qt::DirectConnection);

    m_connectType = Qt::DirectConnection;
}

void Widget::onBtnQueuedClicked()
{
    disconnect(this, 0, 0, 0);
    connect(m_factory, SIGNAL(product()), this, SLOT(onProduct()), Qt::QueuedConnection);

    m_connectType = Qt::QueuedConnection;
}

void Widget::onBtnBlockClicked()
{
    disconnect(this, 0, 0, 0);
    connect(m_factory, SIGNAL(product()), this, SLOT(onProduct()), Qt::BlockingQueuedConnection);

    m_connectType = Qt::BlockingQueuedConnection;
}

void Widget::onBtnUniqueClicked()
{
    disconnect(this, 0, 0, 0);
    connect(m_factory, SIGNAL(product()), this, SLOT(onProduct()), Qt::UniqueConnection);

    m_connectType = Qt::UniqueConnection;
}

void Widget::onProduct()
{
    qDebug() << "=============================";

    switch (m_connectType) {
    case Qt::DirectConnection:
        qDebug() << __FUNCTION__ << "Connect type: Qt::DirectConnection";
        break;
    case Qt::QueuedConnection:
        qDebug() << __FUNCTION__ << "Connect type: Qt::QueuedConnection";
        break;
    case Qt::BlockingQueuedConnection:
        qDebug() << __FUNCTION__ << "Connect type: Qt::BlockingQueuedConnection";
        break;
    case Qt::UniqueConnection:
        qDebug() << __FUNCTION__ << "Connect type: Qt::UniqueConnection";
        break;
    default:
        break;
    }

    if (QThread::currentThreadId() == m_mainThreadId)
        qDebug() << __FUNCTION__ << "主线程";
    else
        qDebug() << __FUNCTION__ << "子线程";
}

