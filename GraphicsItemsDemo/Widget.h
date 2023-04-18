#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QGraphicsScene *m_scene;
    QGraphicsView  *m_view;
    QGraphicsSimpleTextItem *m_simpleTextItem;
    QGraphicsTextItem *m_textItem;

};

#endif // WIDGET_H
