#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      m_moveLabel(NULL)
{
    ui->setupUi(this);
    //移动动画
    m_moveLabel = new QLabel("我是移动标签", this);
    m_moveLabel->setGeometry(50, 50, 100, 40);
    m_moveLabel->setStyleSheet("QLabel {"
                           "    border: 1px solid;"
                           "    border-color: red;"
                           "    border-radius: 5px;"
                           "}");

    QPropertyAnimation *moveAnimation = new QPropertyAnimation(m_moveLabel, "geometry");
    moveAnimation->setDuration(1000);
    moveAnimation->setStartValue(QRect(m_moveLabel->x(),     m_moveLabel->y(),
                                       m_moveLabel->width(), m_moveLabel->height()));
    moveAnimation->setEndValue(QRect(m_moveLabel->x()+400, m_moveLabel->y()+400,
                                      m_moveLabel->width(), m_moveLabel->height()));
    moveAnimation->setEasingCurve(QEasingCurve::OutBounce);

    m_moveBtn = new QPushButton("Move", this);
    m_moveBtn->setGeometry(this->width() - 200, this->y() + 100, 100, 40);
    m_moveBtn->setStyleSheet("QPushButton {"
                         "    border: 2px solid;"
                         "    border-radius: 10px;"
                         "}");

    connect(m_moveBtn, SIGNAL(clicked()), moveAnimation, SLOT(start()));

    //缩放动画
    m_scaleLabel = new QLabel("我是缩放标签", this);
    m_scaleLabel->setGeometry(50, 100, 100, 40);
    m_scaleLabel->setStyleSheet("QLabel {"
                               "    border: 1px solid;"
                               "    border-color: black;"
                               "    border-radius: 5px;"
                               "}");

    QPropertyAnimation *scaleAnimation = new QPropertyAnimation(m_scaleLabel, "geometry");
    scaleAnimation->setDuration(1000);
    scaleAnimation->setStartValue(QRect(m_scaleLabel->x(), m_scaleLabel->y(),
                                        m_scaleLabel->width(), m_scaleLabel->height()));
    scaleAnimation->setEndValue(QRect(m_scaleLabel->x(), m_scaleLabel->y(),
                                      m_scaleLabel->width()*2, m_scaleLabel->height()*2));

    m_scaleBtn = new QPushButton("Scale", this);
    m_scaleBtn->setGeometry(this->width() - 200, this->y() + 200, 100, 40);
    m_scaleBtn->setStyleSheet("QPushButton {"
                              "    border: 2px solid;"
                              "    border-radius: 10px;"
                              "}");

    connect(m_scaleBtn, SIGNAL(clicked()), scaleAnimation, SLOT(start()));

    //移动+缩放动画
    m_moveScaleLabel = new QLabel("我是移动缩放标签", this);
    m_moveScaleLabel->setGeometry(50, 150, 100, 40);
    m_moveScaleLabel->setStyleSheet("QLabel {"
                                    "    border: 1px solid;"
                                    "    border-color: gray;"
                                    "    border-radius: 5px;"
                                    "}");

    QPropertyAnimation *moveScaleAnimation = new QPropertyAnimation(m_moveScaleLabel, "geometry");
    moveScaleAnimation->setDuration(10000);
    moveScaleAnimation->setKeyValueAt(0,   QRect(m_moveScaleLabel->x(), m_moveScaleLabel->y(),
                                                 m_moveScaleLabel->width(), m_moveScaleLabel->height()));
    moveScaleAnimation->setKeyValueAt(0.5, QRect(m_moveScaleLabel->x() + 200, m_moveScaleLabel->y() + 200,
                                                 m_moveScaleLabel->width()*1.414, m_moveScaleLabel->height()*1.414));
    moveScaleAnimation->setKeyValueAt(1,   QRect(m_moveScaleLabel->x() + 200, m_moveScaleLabel->y() + 200,
                                                 m_moveScaleLabel->width()*1.414, m_moveScaleLabel->height()*1.414));

    m_moveScaleBtn = new QPushButton("Move\nScale", this);
    m_moveScaleBtn->setGeometry(this->width() - 200, this->y() + 300, 100, 40);
    m_moveScaleBtn->setStyleSheet("QPushButton {"
                                  "    border: 2px solid;"
                                  "    border-radius: 10px;"
                                  "}");

    connect(m_moveScaleBtn, SIGNAL(clicked()), moveScaleAnimation, SLOT(start()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnClicked()
{
    m_moveLabel->move(450, 450);
}

