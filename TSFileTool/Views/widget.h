#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDateTime>
#include <QButtonGroup>
#include "../Service/TsFixUp/TsFixUp.h"

#define WIDGET_WIDTH  (460)
#define WIDGET_HEIGHT (400)

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
    void onCheckBoxClicked(int index);

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
    enum CheckBox_Index {
        null_Check = -1,
        TwoCols_Check,
        ThreeCols_Check
    };

private:
    Ui::Widget *ui;
    QButtonGroup *m_checkBoxGroup;
    CheckBox_Index m_clickedIndex;
    TsFixUp *m_tsFixUp;

    QString m_tsFilePath;
    QString m_xlsxFilePath;
    QString m_outputFilePath; //outputFile includes .ts and .xlsx

    QString m_fileTips;
};
#endif // WIDGET_H
