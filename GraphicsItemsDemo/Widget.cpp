#include "Widget.h"
#include <QBrush>
#include <QColor>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(600, 400);

    m_scene = new QGraphicsScene(this);
    m_view  = new QGraphicsView(m_scene, this);

    m_simpleTextItem = new QGraphicsSimpleTextItem();
    m_simpleTextItem->setText("This is a QGraphicsSimpleTextItem.");
    m_simpleTextItem->setBrush(QBrush(QColor(0, 0, 0)));

    m_textItem = new QGraphicsTextItem();
    m_textItem->setHtml("<p style=\"background-color:#FFFF00\">通过十六进制设置背景颜色</p>");

//    m_scene->addItem(m_simpleTextItem);
//    m_scene->addItem(m_textItem);

    qDebug() << "Width: " << m_view->width() << " Heigth:" << m_view->height();
}

Widget::~Widget()
{

}
