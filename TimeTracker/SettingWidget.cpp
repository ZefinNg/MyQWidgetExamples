#include "SettingWidget.h"
#include "ui_SettingWidget.h"
#include <QMutexLocker>
#include <QDebug>

// 初始化静态成员变量
QMutex SettingWidget::s_mutex;
SettingWidget* SettingWidget::s_instance = nullptr;

SettingWidget* SettingWidget::getInstance()
{
    if (s_instance == nullptr) {
        QMutexLocker locker(&s_mutex);
        if (s_instance == nullptr) {
            s_instance = new SettingWidget();
        }
    }
    return s_instance;
}

SettingWidget::SettingWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

void SettingWidget::done(int r)
{
    qDebug() << __FUNCTION__ << __LINE__;
    // 保存配置信息
    QDialog::done(r);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}
