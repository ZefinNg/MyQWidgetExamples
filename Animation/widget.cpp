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
    m_moveBtn->setGeometry(this->width() - 200, this->y() + 50, 100, 40);
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
    m_scaleBtn->setGeometry(this->width() - 200, this->y() + 100, 100, 40);
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
    m_moveScaleBtn->setGeometry(this->width() - 200, this->y() + 150, 100, 40);
    m_moveScaleBtn->setStyleSheet("QPushButton {"
                                  "    border: 2px solid;"
                                  "    border-radius: 10px;"
                                  "}");

    connect(m_moveScaleBtn, SIGNAL(clicked()), moveScaleAnimation, SLOT(start()));

    //悬浮窗口
    QPropertyAnimation *transparentAnimation = new QPropertyAnimation(this, "windowOpacity");
    transparentAnimation->setDuration(2000);
    transparentAnimation->setKeyValueAt(0, 1);
    transparentAnimation->setKeyValueAt(0.5, 0);
    transparentAnimation->setKeyValueAt(1, 1);

    m_tipsBtn = new QPushButton("Disappear", this);
    m_tipsBtn->setGeometry(this->width() - 200, this->y() + 200, 100, 40);
    m_tipsBtn->setStyleSheet("QPushButton {"
                             "    border: 2px solid;"
                             "    border-radius: 10px;"
                             "}");

    connect(m_tipsBtn, SIGNAL(clicked()), transparentAnimation, SLOT(start()));

    //悬浮Label
    m_tipsLabel = new QLabel("我是一个悬浮标签！", this);
    m_tipsLabel->setGeometry((this->width()-m_tipsLabel->width())/2, this->height() - 300,
                             160, 80);

    m_tipsLabel->hide();

    QPropertyAnimation *alphaAnimation = new QPropertyAnimation(this, "labelAlpha");
    alphaAnimation->setDuration(3000);
    alphaAnimation->setKeyValueAt(0, 0);
    alphaAnimation->setKeyValueAt(0.3, 125);
    alphaAnimation->setKeyValueAt(0.5, 255);
    alphaAnimation->setKeyValueAt(0.8, 125);
    alphaAnimation->setKeyValueAt(1, 0);
//    alphaAnimation->setLoopCount(-1);

    m_alphaBtn = new QPushButton("Alpha", this);
    m_alphaBtn->setGeometry(this->width() - 200, this->y() + 250, 100, 40);
    m_alphaBtn->setStyleSheet("QPushButton {"
                              "    border: 2px solid;"
                              "    border-radius: 10px;"
                              "}");

    connect(m_alphaBtn, SIGNAL(clicked()), alphaAnimation, SLOT(start()));

    //悬浮窗口
    m_floatingWidget = new FloatinWidget();
    m_floatingWidget->setText("我是一个悬浮窗口.");
    m_floatingWidget->setGeometry(this->x() + this->width()/2 - 200, this->height() - 100,
                                  160, 80);

    m_floatBtn = new QPushButton("Floating", this);
    m_floatBtn->setGeometry(this->width() - 200, this->y() + 300, 100, 40);
    m_floatBtn->setStyleSheet("QPushButton {"
                              "    border: 2px solid;"
                              "    border-radius: 10px;"
                              "}");

    connect(m_floatBtn, SIGNAL(clicked()), m_floatingWidget, SLOT(start()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnClicked()
{
    m_moveLabel->move(450, 450);
}

int Widget::labelAlpha() const
{
    return m_labelAlphaValue;
}

void Widget::setLabelAlpha(int labelAlpha)
{
    m_labelAlphaValue = labelAlpha;
    if (labelAlpha == 0)
        m_tipsLabel->hide();
    else
        m_tipsLabel->show();
    QString qssStyle = QString("background-color: rgba(10, 160, 105, %1);").arg(m_labelAlphaValue);
    m_tipsLabel->setStyleSheet(qssStyle);
}

