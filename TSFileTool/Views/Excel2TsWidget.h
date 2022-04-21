#ifndef EXCEL2TSWIDGET_H
#define EXCEL2TSWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDateTime>
#include <QButtonGroup>
#include "../Service/SourceFileHandler/SourceFileHandler.h"
#include "../Service/TsFixUp/TsFixUp.h"

namespace Ui {
class Excel2TsWidget;
}

class Excel2TsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Excel2TsWidget(QWidget *parent = nullptr);
    ~Excel2TsWidget();

private slots:
    void onBtnSelectExcelClicked();
    void onBtnSelectTsFileClicked();

    void onBtnExcel2TsClicked();
    void onBtnTs2ExcelClicked();
    void onBtnOpenOutputClicked();
    void onBtnExcelStatusClicked();
    void onCheckBoxClicked(int index);

    void onExcelHandlerError(TsExcelHandler::HANDLE_ERROR errorNum);

private:
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
    Ui::Excel2TsWidget *ui;
    QButtonGroup *m_checkBoxGroup;
    CheckBox_Index m_clickedIndex;
    TsFixUp *m_tsFixUp;

    QString m_tsFilePath;
    QString m_xlsxFilePath;
    QString m_outputFilePath; //outputFile includes .ts and .xlsx

    QString m_fileTips;

    SourceFileHandler *m_srcFileHandler;
};

#endif // EXCEL2TSWIDGET_H
