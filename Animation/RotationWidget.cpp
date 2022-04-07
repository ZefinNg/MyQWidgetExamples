#include "RotationWidget.h"
#include <QGridLayout>

RotationWidget::RotationWidget(QWidget *parent) : QWidget(parent)
{
    m_rotaionValue = 0;
    m_timer.setInterval(100);
    m_label = new QLabel(this);

    QGridLayout gridLayout(this);
    gridLayout.addWidget(m_label);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

void RotationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    m_rotaionValue = m_rotaionValue > 360 ? 0 : m_rotaionValue+1;
    int width  = m_pixmap.width();
    int heigth = m_pixmap.height();

    QPixmap tempPixmap(m_pixmap);
    tempPixmap.fill(Qt::transparent);

    QPainter painter(&tempPixmap);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(width/2, heigth/2);
    painter.rotate(m_rotaionValue);
    painter.translate(-(width/2), -(heigth/2));
    painter.drawPixmap(0, 0, m_pixmap);
    painter.end();
    m_label->setPixmap(tempPixmap);
}

void RotationWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
}
