#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget),
      m_stackedWidget(new QStackedWidget(this)),
      m_excel2TsWidget(new Excel2TsWidget(m_stackedWidget)),
      m_excel2ErrorWidget(new Excel2ErrorFileWidget(m_stackedWidget)),
      m_btnPage1(new QPushButton(tr("Page1"), this)),
      m_btnPage2(new QPushButton(tr("Page2"), this))
{
    ui->setupUi(this);
    this->setFixedSize(WIDGET_WIDTH, WIDGET_HEIGHT);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(m_stackedWidget);
    gridLayout->setMargin(0);

    QHBoxLayout *pageBtnLayout = new QHBoxLayout();
    pageBtnLayout->addStretch();
    pageBtnLayout->addWidget(m_btnPage1);
    pageBtnLayout->addWidget(m_btnPage2);
    pageBtnLayout->addStretch();

    gridLayout->addLayout(pageBtnLayout, 1, 0);

    m_stackedWidget->addWidget(m_excel2TsWidget);
    m_stackedWidget->addWidget(m_excel2ErrorWidget);

    connect(m_btnPage1, &QPushButton::clicked, this, &Widget::onBtnPage1Clicked);
    connect(m_btnPage2, &QPushButton::clicked, this, &Widget::onBtnPage2Clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onBtnPage1Clicked()
{
    m_stackedWidget->setCurrentIndex(0);
}

void Widget::onBtnPage2Clicked()
{
    m_stackedWidget->setCurrentIndex(1);
}

