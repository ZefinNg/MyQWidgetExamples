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

private:
    void createDBFile();
    void createTable(QString &tableName);

private:
    void setMainTableView();
    void showTableData(QString tableName);

    void deleteDataFromDB(QString tableName, QString id);
    void insertDataIntoDB(QString tableName, HeroInfo info);

private:
    Ui::Widget *ui;
    QDialog *m_dialog;

    QSqlDatabase m_database;
    QSqlQuery    m_query;
};

#endif // WIDGET_H
