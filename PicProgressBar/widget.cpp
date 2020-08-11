#include "widget.h"
#include <QPainter>
#include <QPainterPath>
#include <QBrush>
#include <QDebug>

#define UPPERLIMIT (100)

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_count(UPPERLIMIT)
{
    this->setFixedSize(799, 440);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/splash.png")));
    setPalette(palette);

    m_progressPixmap.load(":/progressbar.png");

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    m_timer.start(90);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent);
    int progressWidth = (UPPERLIMIT - m_count) * (594-108) / UPPERLIMIT + 108;
    float percent = (UPPERLIMIT - m_count) * 100 / UPPERLIMIT;
    QPixmap tempPixmap = m_progressPixmap.copy(32, 0, 44, 50);

    QPainterPath progressPath;
    progressPath.addRoundRect(103, 205, progressWidth, 44, 99);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(tempPixmap));
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.drawPath(progressPath);
    painter.setPen(QPen(Qt::black));
    painter.drawText(QPointF(397, 335), QString("%1\%").arg(percent));
}

void Widget::onTimeOut()
{
    if (m_count != 0) {
        m_count -=1;
        repaint();
    }
    else
        m_timer.stop();
}
