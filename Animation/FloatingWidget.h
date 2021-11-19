#ifndef FLOATINGWIDGET_H
#define FLOATINGWIDGET_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

class FloatinWidget : public QDialog
{
    Q_OBJECT

public:
    FloatinWidget(QWidget *parent = NULL);

    void setGeometry(int x, int y, int w, int h);

    QString text() const;
    void setText(const QString &text);

    void start();

signals:
    void finished();

private slots:
    void onAnimationFinished();

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    QLabel *m_label;

    QString m_text;

    QPropertyAnimation *m_moveShowAnimation;
    QPropertyAnimation *m_moveUpAnimation;
    QPropertyAnimation *m_opacityAnimation;
    QPropertyAnimation *m_moveDownAnimation;
    QSequentialAnimationGroup *m_animationGroup;
};

#endif // FLOATINGWIDGET_H
