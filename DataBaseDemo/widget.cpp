#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPalette>
#include <QScrollBar>
#include <QAbstractItemView>

#define FILE_NAME "ThreeKindoms.db"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置背景
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/Images/ThreeKingdomsKill.jpg")));
    setPalette(palette);

    //创建数据库文件
    this->createDBFile();

    //创建数据表
    QString tableName = "ShuKingdom";
    this->createTable(tableName);

    tableName = "WeiKingdom";
    this->createTable(tableName);

    tableName = "WuKingdom";
    this->createTable(tableName);

    tableName = "OtherKingdom";
    this->createTable(tableName);

    //固定界面大小
    this->setMaximumSize(1000, 600);
    this->setMinimumSize(1000, 600);

    //设置标题
    this->setWindowTitle(tr("三国英雄信息一览表"));

    //表头数据
    QStringList headerList;
    headerList << tr("索引") << tr("势力") << tr("姓名")
               << tr("字")   << tr("职位") << tr("坐骑")
               << tr("武器") << tr("生卒时间") << tr("谥号")
               << tr("相关典故") << tr("备注");
    ui->mainTableWidget->setColumnCount(headerList.size());

    //For test
    ui->mainTableWidget->setRowCount(30);

    //设置表头数据
    ui->mainTableWidget->setHorizontalHeaderLabels(headerList);

    //设置QTableWidget的显示
    this->setMainTableView();

    //显示数据
    this->showTableData("ShuKingdom");
    this->showTableData("WeiKingdom");
    this->showTableData("WuKingdom");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::createDBFile()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", "ThreeKindoms");
    m_database.setDatabaseName(QString(QCoreApplication::applicationDirPath() + "/" + FILE_NAME));
    /*
     * 如果不存在文件，则会先创建文件;
     * 存在则直接打开。
     */
    if (!m_database.open())
        qDebug() << "Open database file failed.";
    else
        qDebug() << "Open database file success.";

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
                                       "id INTEGER PRIMARY KEY NOT NULL,"
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
}

void Widget::setMainTableView()
{
    //设置QTableWidge控件背景透明
    QPalette tablePalette = ui->mainTableWidget->palette();
    tablePalette.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    ui->mainTableWidget->setPalette(tablePalette);

    //TODO:设置QTableWidget表头透明
    //这里暂时设置为与背景图颜色相近
    ui->mainTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                           "background-color: #A99B78;" //背景图片相近颜色
                                                           "color: white;"              //字体颜色
                                                           "font-size: 24px;"           //字体大小
                                                           "}");

    //设置行头不显示
    ui->mainTableWidget->verticalHeader()->setVisible(false);

    //设置水平滚动条样式
    ui->mainTableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{"
                                                              "height:18px;"
                                                              "background:#A99B78;"
                                                              "padding-top:3px;"
                                                              "padding-bottom:3px;"
                                                              "padding-left:30px;"
                                                              "padding-right:30px;}"
                                                              "QScrollBar::handle:horizontal{"
                                                              "background:#5d5437;"
                                                              "border-radius:6px;"
                                                              "min-width:80px;}"
                                                              "QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal"
                                                              "{border: none;"
                                                              "background: none;"
                                                              "color: none;}"
                                                              );

    //设置垂直滚动条样式
    ui->mainTableWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"
                                                            "width:18px;"
                                                            "background:#A99B78;"
                                                            "padding-top:30px;"
                                                            "padding-bottom:30px;"
                                                            "padding-left:3px;"
                                                            "padding-right:3px;}"
                                                            "QScrollBar::handle:vertical{"
                                                            "background:#5d5437;"
                                                            "border-radius:6px;"
                                                            "min-height:80px;}"
                                                            "QScrollBar::down-arrow:vertical, QScrollBar::up-arrow:vertical"
                                                            "{border: none;"
                                                            "background: none;"
                                                            "height:0px;"
                                                            "color: none;}"
                                                            );

    ui->mainTableWidget->setStyleSheet("QTableWidget{"
                                           "color: #2e2f30;"
                                           "font-size: 20px;"
                                           "text-align: middle;"
    //                                       "gridline-color:white;"
                                           "}");

    ui->mainTableWidget->setStyleSheet("QTableWidget::item::selected{"
                                       "color:white;"                // 每个单元格被选中时 字体颜色
                                       "background:#75674d;}"        // 每个单元格被选中时 背景颜色
                                       );

    //去除选中的虚线框
    ui->mainTableWidget->setFocusPolicy(Qt::NoFocus);

    //设置文本省略显示的模式
    ui->mainTableWidget->setTextElideMode(Qt::ElideRight);

    //设置表头自适应
//    ui->mainTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //设置选中为选中一行而非一个单元格
    ui->mainTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置只能选中一行
    ui->mainTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    //设置不显示网格
    ui->mainTableWidget->setShowGrid(false);

}

void Widget::showTableData(QString tableName)
{
    if (!m_database.isOpen()) {
        qDebug() << "Database has not opened.";
        if (!m_database.open()) {
            qDebug() << "Open database failed.";
            return;
        }
    }

    QString queryAllSql = QString("SELECT * FROM %1").arg(tableName);

    QSqlQuery query(m_database);
    if (!query.prepare(queryAllSql)) {
        qDebug() << "Query prepare failed.";
        return;
    }

    if (!query.exec()) {
        qDebug() << "Query exec failed.";
        return;
    }

    int rowCount = ui->mainTableWidget->rowCount();
    QString itemData = "";

    while (query.next()) {
        ui->mainTableWidget->setRowCount(rowCount+1);
        for (int i = 0; i < ui->mainTableWidget->columnCount(); i++) {
            itemData = query.value(i).toString();
            QTableWidgetItem *item = new QTableWidgetItem(itemData);
            //设置文本对齐方式
            item->setTextAlignment(Qt::AlignCenter);

            ui->mainTableWidget->setItem(rowCount, i, item);
        }
    }
}
