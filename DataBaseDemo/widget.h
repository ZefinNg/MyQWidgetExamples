#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void createDBFile();
    void createTable(QString &tableName);

private:
    void setMainTableView();

private:
    Ui::Widget *ui;

    QSqlDatabase m_database;
};

#endif // WIDGET_H
