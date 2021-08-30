#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ExcelHandler.h"

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
    void onBtnOpenClicked();

    void onExcelHandlerError(ExcelHandler::HANDLE_ERROR errorNum);
#if 0
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
    ExcelHandler *m_excelHandler;
};
#endif // WIDGET_H
