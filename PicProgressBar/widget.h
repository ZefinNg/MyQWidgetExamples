#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPaintEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *paintEvent);

private slots:
    void onTimeOut();

private:
    QLabel *m_backgroundLabel;
    QPixmap m_progressPixmap;
    QTimer m_timer;

    int m_count;
};

#endif // WIDGET_H
