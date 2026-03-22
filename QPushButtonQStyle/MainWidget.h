#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "AnimateButtonStyle.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    AnimateButtonStyle *m_btn1Style;
};
#endif // MAINWIDGET_H
