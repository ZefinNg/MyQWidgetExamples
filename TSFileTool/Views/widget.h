#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include "Excel2TsWidget.h"
#include "Excel2ErrorFileWidget.h"

#define WIDGET_WIDTH  (400)
#define WIDGET_HEIGHT (300)

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
    void onBtnPage1Clicked();
    void onBtnPage2Clicked();

private:
    Ui::Widget *ui;
    QStackedWidget *m_stackedWidget;
    Excel2TsWidget *m_excel2TsWidget;
    Excel2ErrorFileWidget *m_excel2ErrorWidget;

    QPushButton *m_btnPage1;
    QPushButton *m_btnPage2;
};
#endif // WIDGET_H
