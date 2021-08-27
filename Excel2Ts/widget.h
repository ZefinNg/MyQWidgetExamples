#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
#if 0
    void onBtnOpenClicked();
    void onBtnCloseClicked();
    void onBtnSetTitleClicked();
    void onBtnSetSheetNameClicked();
    void onBtnAddSheetClicked();
    void onBtnDeleteSheetClicked();
    void onBtnAddCell();
#endif

private:
#if 0
    void getExcelFileInfo();
#endif

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
