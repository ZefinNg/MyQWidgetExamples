#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ScrollLabel.h"
#include "TextTicker.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    ScrollLabel *m_scrollLabel1;
    TextTicker *m_textTicker1;
};

#endif // WIDGET_H
