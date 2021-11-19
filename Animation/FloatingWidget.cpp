#include "FloatingWidget.h"
#include <QGridLayout>
#include <QDebug>

FloatinWidget::FloatinWidget(QWidget *parent) :
    QDialog(parent),
    m_x(0),
    m_y(0),
    m_width(100),
    m_height(40),
    m_label(NULL),
    m_text("")
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_label = new QLabel(m_text, this);
    m_label->setStyleSheet("QLabel {"
                           "    color: white;"
//                           "    border: 2px solid;"
                           "    border-radius: 10px;"
                           "    background-color: gray;"
                           "}");

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(m_label);
    gridLayout->setMargin(0);

    m_animationGroup = new QSequentialAnimationGroup(this);

    m_moveShowAnimation = new QPropertyAnimation(this, "windowOpacity");
    m_moveShowAnimation->setDuration(10);
    m_moveShowAnimation->setStartValue(1);
    m_moveShowAnimation->setEndValue(1);

    m_moveUpAnimation = new QPropertyAnimation(this, "geometry");
    m_moveUpAnimation->setDuration(500);
    m_moveUpAnimation->setStartValue(QRect(m_x, m_y+20, m_width, m_height));
    m_moveUpAnimation->setEndValue(QRect(m_x, m_y, m_width, m_height));

    m_opacityAnimation = new QPropertyAnimation(this, "windowOpacity");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setKeyValueAt(0, 1);
    m_opacityAnimation->setKeyValueAt(0.2, 0.8);
    m_opacityAnimation->setKeyValueAt(0.4, 0.6);
    m_opacityAnimation->setKeyValueAt(0.6, 0.4);
    m_opacityAnimation->setKeyValueAt(0.8, 0.2);
    m_opacityAnimation->setKeyValueAt(1, 0);

//    m_animationGroup->addAnimation(m_moveShowAnimation);
    m_animationGroup->addAnimation(m_moveUpAnimation);
    m_animationGroup->addAnimation(m_opacityAnimation);

    connect(m_animationGroup, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
//    this->hide();
}

void FloatinWidget::setGeometry(int x, int y, int w, int h)
{
    m_x = x;
    m_y = y;
    m_width  = w;
    m_height = h;

    m_moveUpAnimation->setStartValue(QRect(m_x, m_y+20, m_width, m_height));
    m_moveUpAnimation->setEndValue(QRect(m_x, m_y, m_width, m_height));

    return QWidget::setGeometry(x, y, w, h);
}

QString FloatinWidget::text() const
{
    return m_text;
}

void FloatinWidget::setText(const QString &text)
{
    m_text = text;
    m_label->setText(m_text);
}

void FloatinWidget::start()
{
    this->show();
    qDebug() << this->geometry();
    m_animationGroup->start();
}

void FloatinWidget::onAnimationFinished()
{
    this->setGeometry(m_x, (m_y+20), m_width, m_height);
    qDebug() << this->geometry();
    emit finished();
}
