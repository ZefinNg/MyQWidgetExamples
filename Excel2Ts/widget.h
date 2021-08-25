#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ExcelReadWriter.h"

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
    void onBtnCloseClicked();

private:
    Ui::Widget *ui;
    ExcelReadWrite *m_excelRW;
};
#endif // WIDGET_H
