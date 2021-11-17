#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onBtnClicked();

private:
    Ui::Widget *ui;

    QLabel *m_moveLabel;
    QPushButton *m_moveBtn;

    QLabel *m_scaleLabel;
    QPushButton *m_scaleBtn;

    QLabel *m_moveScaleLabel;
    QPushButton *m_moveScaleBtn;


};
#endif // WIDGET_H
