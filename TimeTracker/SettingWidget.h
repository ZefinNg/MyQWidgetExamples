#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QDialog>
#include <QMutex>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QDialog
{
    Q_OBJECT

public:
    static SettingWidget* getInstance();
    ~SettingWidget();

private:
    explicit SettingWidget(QWidget *parent = nullptr);

private:
    Ui::SettingWidget *ui;
    static QMutex s_mutex;
    static SettingWidget* s_instance;

    // QDialog interface
public slots:
    void done(int r);
};

#endif // SETTINGWIDGET_H
