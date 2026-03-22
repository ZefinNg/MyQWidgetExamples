#include "Widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
#if 0
    m_scrollLabel1 = new ScrollLabel(this);
    m_scrollLabel1->setText("当windows系统设置文本显示比例不是100%的时候,这里设置字体大小号数并不意味着文字的像素大小就是这个号数");
#else
    m_textTicker1 = new TextTicker(this);
#endif

//    QGridLayout *widgetLayout = new QGridLayout;
//    widgetLayout->addWidget(m_scrollLabel1);
//    this->setLayout(widgetLayout);

//    this->resize(100, 100);
//    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
}

Widget::~Widget()
{

}
