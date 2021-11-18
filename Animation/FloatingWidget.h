#ifndef FLOATINGWIDGET_H
#define FLOATINGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class FloatinWidget : public QWidget
{
    Q_OBJECT

public:
    FloatinWidget(QWidget *parent = NULL);

    void setGeometry(int x, int y, int w, int h);

    QString text() const;
    void setText(const QString &text);

public slots:
    void start();

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    QLabel *m_label;

    QString m_text;

    QPropertyAnimation *m_moveAnimation;
    QPropertyAnimation *m_opacityAnimation;
    QSequentialAnimationGroup *m_animationGroup;
};

#endif // FLOATINGWIDGET_H
