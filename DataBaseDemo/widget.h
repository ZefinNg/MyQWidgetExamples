#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDialog>

#include "Domains/HeroInfo.h"
#include "View/InputInfoDialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onCellDoubleClicked(int row, int column);
    void onBtnDeleteData();
    void onBtnInsertData();
    void onBtnModifyData();

    void onAddData(HeroInfo heroInfo);

private:
    void createDBFile();
    void createTable(QString &tableName);

    void setMainTableView();
    void showTableData(QString tableName);

    bool deleteDataFromDB(QString tableName, QString id);
    bool insertDataIntoDB(QString tableName, HeroInfo info);

    void showAllTable();

private:
    Ui::Widget *ui;
    InputInfoDialog *m_infoDialog;

    QSqlDatabase m_database;
    QSqlQuery    m_query;
};

#endif // WIDGET_H
