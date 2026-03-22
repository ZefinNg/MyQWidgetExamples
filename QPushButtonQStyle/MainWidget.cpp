#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    m_btn1Style = new AnimateButtonStyle("Fusion");
    ui->pushButton1->setStyle(m_btn1Style);
}

MainWidget::~MainWidget()
{
    delete ui;
}
