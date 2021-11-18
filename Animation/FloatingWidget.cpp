#include "FloatingWidget.h"
#include <QGridLayout>

FloatinWidget::FloatinWidget(QWidget *parent) :
    QWidget(parent),
    m_x(0),
    m_y(0),
    m_width(100),
    m_height(40),
    m_label(NULL),
    m_text("")
{
    this->setWindowFlag(Qt::FramelessWindowHint);
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

    m_moveAnimation = new QPropertyAnimation(this, "geometry");
    m_moveAnimation->setDuration(1000);
    m_moveAnimation->setStartValue(QRect(this->x(), this->y() + 20, this->width(), this->height()));
    m_moveAnimation->setEndValue(QRect(this->x(), this->y() - 20, this->width(), this->height()));

    m_opacityAnimation = new QPropertyAnimation(this, "windowOpacity");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setKeyValueAt(0, 1);
    m_opacityAnimation->setKeyValueAt(0.2, 0.8);
    m_opacityAnimation->setKeyValueAt(0.4, 0.6);
    m_opacityAnimation->setKeyValueAt(0.6, 0.4);
    m_opacityAnimation->setKeyValueAt(0.8, 0.2);
    m_opacityAnimation->setKeyValueAt(1, 0);

    m_animationGroup->addAnimation(m_moveAnimation);
    m_animationGroup->addAnimation(m_opacityAnimation);

//    this->hide();
}

void FloatinWidget::setGeometry(int x, int y, int w, int h)
{
    m_x = x;
    m_y = y;
    m_width  = w;
    m_height = h;

    m_moveAnimation->setStartValue(QRect(m_x, m_y + 20, m_width, m_height));
    m_moveAnimation->setEndValue(QRect(m_x, m_y, m_width, m_height));

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
    m_animationGroup->start();
}
