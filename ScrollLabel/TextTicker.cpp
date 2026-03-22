#include "textticker.h"
#include <QTimer>

TextTicker::TextTicker(QWidget *parent)
    : QWidget(parent)
{
    m_curIndex = 0;//当前角码
    m_showText = "This is a textTicker Text!";//显示的文字
    m_label = new QLabel(this);
    m_label->setMinimumWidth(300);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TextTicker::showTicker);
    timer->start(100);//定时器
}

TextTicker::~TextTicker()
{

}

void TextTicker::showTicker()
{
    int iSize = m_showText.size();
    if (m_curIndex < 0)
        m_curIndex = iSize;
    m_label->setText(m_showText.mid(m_curIndex--));
    //m_label->setText(m_showText.right(iSize - m_curIndex--));
}
