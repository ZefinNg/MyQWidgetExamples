#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(onBtnCloseClicked()));

    m_excelRW = new ExcelReadWrite("C:\\Users\\zefeng.wu\\Desktop\\万孚 POCT 数据管理系统传输日志.xlsx", this);

    qDebug() << m_excelRW->title();
    qDebug() << m_excelRW->getWorkSheetCount();
}

Widget::~Widget()
{
    m_excelRW->closeFile();
    delete ui;
}

void Widget::onBtnCloseClicked()
{
    m_excelRW->closeFile();
}
