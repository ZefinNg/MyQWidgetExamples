#include "LuckyDrawWidget.h"
#include <QPainter>
#include <QPixmap>
#include <QTime>
#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QApplication>

LuckyDrawWidget::LuckyDrawWidget(QWidget *parent)
    : QWidget(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    this->setMouseTracking(true);

    m_bgPixmap      = new QPixmap(":/image/background.png");
    m_pointerPixmap = new QPixmap(":/image/pointer.png");

    this->setFixedSize(m_bgPixmap->width(), m_bgPixmap->height());
    m_pointerRect = new QRect((this->width() - m_pointerPixmap->width())/2, (this->height() - m_pointerPixmap->height() - 50)/2,
                                 m_pointerPixmap->width(), m_pointerPixmap->height());
}

LuckyDrawWidget::~LuckyDrawWidget()
{

}

int LuckyDrawWidget::rotation() const
{
    return m_rotation;
}

void LuckyDrawWidget::setRotation(int rotation)
{
    m_rotation = rotation;
    update();
}

void LuckyDrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.save();

    int width = this->width();
    int height = this->height();

    //中心偏移至窗口中心位置
    painter.translate(width/2, height/2);
    //旋转角度
    painter.rotate(-1 * m_rotation);
    painter.drawPixmap(QRect(0 - width/2, 0 - height/2,
                             m_bgPixmap->width(), m_bgPixmap->height()), *m_bgPixmap);
    painter.restore();

    painter.drawPixmap(*m_pointerRect, *m_pointerPixmap);
    QWidget::paintEvent(event);
}

void LuckyDrawWidget::mousePressEvent(QMouseEvent *event)
{
    if (qApp->mouseButtons() == Qt::LeftButton) {
        QRegion ellispeRegion(*m_pointerRect, QRegion::Ellipse);
        if (ellispeRegion.contains(event->pos())) {
            int rotationRand = qrand() % 360 + 360 * 3;
            m_rotation = 0;
            QPropertyAnimation *animation = new QPropertyAnimation(this, "rotation");
            animation->setEasingCurve(QEasingCurve::OutCubic);
            animation->setDuration(5000);
            animation->setStartValue(0);
            animation->setEndValue(rotationRand);

//            connect(animation, SIGNAL(finished()), this, SLOT(onRotationFinished()));
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }

    QWidget::mousePressEvent(event);
}

void LuckyDrawWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void LuckyDrawWidget::onRotationFinished()
{
    float rotation = m_rotation - 360 * 3;
    int currentIndex = 0;
    for (int i = 0; i < 12; i++) {
        rotation -= 30;
    }
}
