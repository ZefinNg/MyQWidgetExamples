#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDateTime>
#include "../Service/TsParser/TsFixUp.h"

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
    void onBtnSelectExcelClicked();
    void onBtnSelectTsFileClicked();

    void onBtnStartConvertClicked();
    void onBtnOpenOutputClicked();

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
    TsFixUp *m_tsFixUp;
    QString m_tsFilePath;
    QString m_outputPath;
};
#endif // WIDGET_H
