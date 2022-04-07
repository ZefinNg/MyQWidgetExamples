#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDateTime>
#include "../Service/TsFixUp/TsFixUp.h"

#define WIDGET_WIDTH  (460)
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
    void onBtnSelectExcelClicked();
    void onBtnSelectTsFileClicked();

    void onBtnExcel2TsClicked();
    void onBtnTs2ExcelClicked();
    void onBtnOpenOutputClicked();
    void onBtnExcelStatusClicked();

    void onExcelHandlerError(TsExcelHandler::HANDLE_ERROR errorNum);
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
    void initView();
    bool createFile(const QString &suffix);
    void setExcelNormalStatus(bool isNormal);

private:
    Ui::Widget *ui;
    TsFixUp *m_tsFixUp;

    QString m_tsFilePath;
    QString m_xlsxFilePath;
    QString m_outputFilePath; //outputFile includes .ts and .xlsx

    QString m_fileTips;
};
#endif // WIDGET_H
