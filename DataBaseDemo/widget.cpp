#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

#define FILE_NAME "ThreeKindoms.db"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
#if 1
    //判断文件是否存在
    QFileInfo fileInfo(QString(QCoreApplication::applicationDirPath() + "/" + FILE_NAME));
    if (!fileInfo.exists()) {
        //创建文件
        this->createDBFile();
    }
    QString shuTable = "ShuKingdom";
    this->createTable(shuTable);
#else
    this->createDBFile();
#endif
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createDBFile()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", "ThreeKindoms");
    m_database.setDatabaseName(QString(QCoreApplication::applicationDirPath() + "/" + FILE_NAME));
    if (!m_database.open())
        qDebug() << "Open database file failed.";
    else
        qDebug() << "Open database file success.";

//    QSqlQuery query(m_database);
//    query.exec("CREATE TABLE student(id int primary key,"
//               "name varchar(20))");

}

void Widget::createTable(QString &tableName)
{
    if (!m_database.isOpen()) {
        if (!m_database.open())
            qDebug() << "ERROR:" << m_database.lastError();
    }

    QString isExistCommand(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tableName));
    QString createTableCommand(QString("CREATE TABLE %1 "
                                       "("
                                       "id INTEGER NOT NULL,"
                                       "name TEXT NOT NULL,"
                                       "styleName TEXT,"
                                       "faciton TEXT,"
                                       "position TEXT,"
                                       "mount TEXT,"
                                       "weapon TEXT,"
                                       "birthAndDeathTime TEXT,"
                                       "posthumounsTitle TEXT,"
                                       "allusion TEXT,"
                                       "tips TEXT"
                                       ");").arg(tableName));

    QSqlQuery query(m_database);
    if (!query.exec(isExistCommand))
        qDebug() << "ERROR:" << query.lastError();
/*
    if (query.next()) {
        //不存在数据表
        if (query.value(0).toInt() == 0) {
            //创建数据表
            query.prepare(createTableCommand);
            if (!query.exec())
                qDebug() << "Create table failed.";
            else
                qDebug() << "Create" << tableName << "success.";
        }
    }
    */
}
