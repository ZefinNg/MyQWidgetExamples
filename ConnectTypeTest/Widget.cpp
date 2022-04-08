#include "Widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_btnAutoConnect(new QPushButton("Auto", this)),
      m_btnDirectConnect(new QPushButton("Direct", this)),
      m_btnQueuedConnect(new QPushButton("Queued", this)),
      m_btnBlockConnect(new QPushButton("Block", this)),
      m_btnUniqueConnect(new QPushButton("Unique", this)),
      m_autoSlotInvokedTimes(0),
      m_directSlotInvokedTimes(0),
      m_queuedSlotInvokedTimes(0),
      m_blockSlotInvokedTimes(0),
      m_uniqueSlotInvokedTimes(0),
      m_debugBrowser(new QTextBrowser(this))
{
    QVBoxLayout *widgetLayout = new QVBoxLayout(this);

    QHBoxLayout *btnHorizonalLayout = new QHBoxLayout(this);
    btnHorizonalLayout->addWidget(m_btnAutoConnect);
    btnHorizonalLayout->addWidget(m_btnDirectConnect);
    btnHorizonalLayout->addWidget(m_btnQueuedConnect);
    btnHorizonalLayout->addWidget(m_btnBlockConnect);
    btnHorizonalLayout->addWidget(m_btnUniqueConnect);

    widgetLayout->addLayout(btnHorizonalLayout);
    widgetLayout->addWidget(m_debugBrowser);

    m_debugBrowser->setEnabled(false);
}

Widget::~Widget()
{
}

void Widget::onBtnAutoClicked()
{
    m_autoSlotInvokedTimes++;
    QString tips("Auto slot invoked times:%1").arg(m_autoSlotInvokedTimes);

    m_debugBrowser->append(tips);
}

void Widget::onBtnDirectClicked()
{

}

void Widget::onBtnQueuedClicked()
{

}

void Widget::onBtnBlockClicked()
{

}

void Widget::onBtnUniqueClicked()
{

}

