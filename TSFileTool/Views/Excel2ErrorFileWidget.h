#ifndef EXCEL2ERRORFILEWIDGET_H
#define EXCEL2ERRORFILEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include "../Service/SourceFileHandler/SourceFileHandler.h"

namespace Ui {
class Excel2ErrorFileWidget;
}

class Excel2ErrorFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Excel2ErrorFileWidget(QWidget *parent = nullptr);
    ~Excel2ErrorFileWidget();

private slots:
    void onBtnSelectExcelClicked();
    void onBtnSecectErrorFileClicked();

    void onBtnExcel2ErrorFileClicked();
    void onBtnErrorFile2ExcelClicked();

private:
    void initView();
    void layoutView();
    void drawView();

private:
    Ui::Excel2ErrorFileWidget *ui;

    QPushButton *m_btnSelectExcel;
    QLineEdit   *m_lineEditExcelPath;
    QPushButton *m_btnSelectErrorFile;
    QLineEdit   *m_lineEditErrorFilePath;

    QPushButton *m_btnExcel2Txt;
    QPushButton *m_btnTxt2Excel;

    QString m_excelFile;
    QString m_errorFile;

    QString m_outputFilePath;

    SourceFileHandler *m_srcFileHandler;
};

#endif // EXCEL2ERRORFILEWIDGET_H
