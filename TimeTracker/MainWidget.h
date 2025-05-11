#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QTimer>
#include <QDateTime>
#include <QMap>
#include <QSystemTrayIcon>
#include <QMenu>
#include "DatabaseManager/DatabaseManager.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    bool isRunning(const wchar_t* processName);

private slots:
    void onSelectAppBtnClicked();
    void onSettingBtnClicked();
    void onTrackerTimer();

private:
    void initView();
    void initSystemTray();
    void updateAppInfo();

private:
    // View
    QFormLayout *m_formLayout;
    QPushButton *m_selectAppBtn;
    QPushButton *m_settingBtn;
    QMap<QString, QLabel*> m_timeLabelMap;

    QTimer *m_trackerTimer;
    QString m_trackerApplication;
    QDateTime m_startTime;
};

#endif // MAINWIDGET_H
