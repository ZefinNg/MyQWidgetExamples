#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include "FloatingWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int labelAlpha READ labelAlpha WRITE setLabelAlpha);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void onBtnClicked();

private:
    int labelAlpha() const;
    void setLabelAlpha(int labelAlpha);

private:
    Ui::Widget *ui;

    QLabel *m_moveLabel;
    QPushButton *m_moveBtn;

    QLabel *m_scaleLabel;
    QPushButton *m_scaleBtn;

    QLabel *m_moveScaleLabel;
    QPushButton *m_moveScaleBtn;

    QPushButton *m_tipsBtn;

    int m_labelAlphaValue;
    QLabel *m_tipsLabel;
    QPushButton *m_alphaBtn;

    FloatinWidget *m_floatingWidget;
    QPushButton *m_floatBtn;
};
#endif // WIDGET_H
