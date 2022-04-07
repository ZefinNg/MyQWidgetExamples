#ifndef ROTATIONWIDGET_H
#define ROTATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QLabel>

class RotationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RotationWidget(QWidget *parent = nullptr);

    void setPixmap(const QPixmap &pixmap);

    void start();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

private:
    QPixmap m_pixmap;
    QTimer  m_timer;
    int     m_rotaionValue;
    QLabel *m_label;
};

#endif // ROTATIONWIDGET_H
