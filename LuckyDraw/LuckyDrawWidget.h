#ifndef LUCKYDRAWWIDGET_H
#define LUCKYDRAWWIDGET_H

#include <QWidget>

class LuckyDrawWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)
public:
    LuckyDrawWidget(QWidget *parent = 0);
    ~LuckyDrawWidget();

    int rotation() const;
    void setRotation(int rotation);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private slots:
    void onRotationFinished();

private:
    int m_rotation;
    QPixmap *m_bgPixmap;
    QPixmap *m_pointerPixmap;
    QRect *m_pointerRect;
};

#endif // LUCKYDRAWWIDGET_H
