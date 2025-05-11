#include "MainWidget.h"

#include <windows.h>
#include <tlhelp32.h>

#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVBoxLayout>

#define CONFIG_FILE_NAME ("config.ini")

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_formLayout(new QFormLayout()),
      m_selectAppBtn(new QPushButton(tr(u8"选择软件"), this)),
      m_settingBtn(new QPushButton(tr(u8"设置"), this)),
      m_trackerTimer(new QTimer(this)),
      m_trackerApplication(""),
      m_startTime(QDateTime()) {
#if 0
    const wchar_t* appName = L"notepad++.exe";
    qDebug() << __FUNCTION__ << __LINE__ << appName;

    std::wstring wstr(appName); // 将宽字符数据转换为 std::wstring
    QString str = QString::fromStdWString(wstr); // 使用 QString::fromStdWString 方法进行转换
    qDebug() << __FUNCTION__ << __LINE__ << str;

    if (isRunning(appName))
        qDebug() << appName << " is running.";
    else
        qDebug() << appName << " is not running.";
#else
    // ConfigManager::getInstance()->setConfigFile(QCoreApplication::applicationDirPath() + "/" + CONFIG_FILE_NAME);

    this->initView();
    this->updateAppInfo();

    m_trackerTimer->setInterval(1000 * 30);
    connect(m_trackerTimer, &QTimer::timeout, this, &MainWidget::onTrackerTimer);
    m_trackerTimer->start();
#endif
}

MainWidget::~MainWidget() {
}

bool MainWidget::isRunning(const wchar_t *processName) {
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &processEntry)) {
        do {
            if (wcscmp(processEntry.szExeFile, processName) == 0) {
                CloseHandle(snapshot);
                return true;
            }
        } while (Process32Next(snapshot, &processEntry));
    }
    CloseHandle(snapshot);
    return false;
}

void MainWidget::onSelectAppBtnClicked() {
    QFileInfo fileInfo(QFileDialog::getOpenFileName(this, tr(u8"选择软件"),
                                                    QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                    tr("Applicantion (*.exe)")));
    qDebug() << __FUNCTION__ << __LINE__ << fileInfo.fileName();
    if (fileInfo.fileName().isEmpty())
        return;
    else {
        auto appInfoMap = DatabaseManager::getInstance()->appInfoMap();
        // 数据库中已经记录了该app的上一次启动时间，更新该时间
        if (appInfoMap->contains(fileInfo.fileName().toStdString())) {
            ApplicationInfo tempAppInfo = appInfoMap->value(fileInfo.fileName().toStdString());
            tempAppInfo.setLastLaunchTime(QDateTime::currentSecsSinceEpoch());

            DatabaseManager::getInstance()->appInfoMap()->insert(tempAppInfo.appName().toStdString(), tempAppInfo);
        } else {
            // 第一次加入该app的记录
            auto appInfo = ApplicationInfo();
            appInfo.setAppName(fileInfo.fileName());
            appInfo.setFirstLaunchTime(QDateTime::currentSecsSinceEpoch());
            appInfo.setAppPath(fileInfo.absoluteFilePath());
            appInfo.setLastLaunchTime(QDateTime::currentSecsSinceEpoch());
            appInfo.setTotalRunningTime(0);
            DatabaseManager::getInstance()->insertAppInfoToDb(appInfo);

            // 更新界面
            QLabel *appLabel = new QLabel(appInfo.appName());
            QLabel *timeLabel = new QLabel(QString(u8"%1时%2分").arg(appInfo.totalRunningTime() / 60 / 60).arg(appInfo.totalRunningTime() / 60 % 60));
            m_formLayout->addRow(appLabel, timeLabel);
            m_timeLabelMap.insert(appInfo.appName(), timeLabel);
        }

        m_trackerApplication = fileInfo.fileName();

        if (isRunning(m_trackerApplication.toStdWString().c_str())) {
            m_startTime = QDateTime::currentDateTime();
            qDebug() << __FUNCTION__ << __LINE__ << "Start Time:" << m_startTime;
        }

        m_trackerTimer->start();
    }
}

void MainWidget::onSettingBtnClicked() {
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWidget::onTrackerTimer() {
    auto appInfoMap = DatabaseManager::getInstance()->appInfoMap();

    // 遍历所有app的运行状态，更新运行时间
    for (auto it = appInfoMap->begin(); it != appInfoMap->end(); ++it) {
        if (isRunning(it->appName().toStdWString().c_str())) {
            // 计算运行时间
            qint64 currentTimeStamp = QDateTime::currentSecsSinceEpoch();

            if (it->isActiveFirstTime()) {
                it->setIsActiveFirstTime(false);
                it->setLastLaunchTime(currentTimeStamp);
            }

            // 计算运行时间差值
            qint64 deltaSecs = currentTimeStamp - it->lastLaunchTime();
            if (deltaSecs >= 60) {
                // 程序运行时间超过1分钟，更新数据库中的记录
                it->setLastLaunchTime(currentTimeStamp);
                it->setTotalRunningTime(it->totalRunningTime() + deltaSecs);
                DatabaseManager::getInstance()->updateApplicationInfo(*it);
            }
            qDebug() << __FUNCTION__ << __LINE__ << "deltaSecs:" << deltaSecs;

            // 显示运行时间
            auto minutes = it->totalRunningTime() / 60;
            auto hours = minutes / 60;
            QString timeString = QString(u8"%1时%2分").arg(hours).arg(minutes % 60);
            m_timeLabelMap.value(it->appName())->setText(timeString);
        } else {
            qDebug() << __FUNCTION__ << __LINE__ << u8"未检测到程序正在运行:" << it->appName();
        }
    }
}

void MainWidget::initView() {
    this->initSystemTray();

    m_formLayout->addRow(new QLabel(tr(u8"软件名称")), new QLabel(tr(u8"已运行")));
    m_formLayout->setSpacing(20);

    auto appInfoMap = DatabaseManager::getInstance()->appInfoMap();

    for (auto it = appInfoMap->begin(); it != appInfoMap->end(); ++it) {
        QLabel *appLabel = new QLabel(it->appName());
        QLabel *appTimeLabel = new QLabel(QString(u8"%1时%2分").arg(it->totalRunningTime() / 60 / 60).arg(it->totalRunningTime() / 60 % 60));
        m_formLayout->addRow(appLabel, appTimeLabel);
        m_timeLabelMap.insert(it->appName(), appTimeLabel);
    }

    QVBoxLayout *overallLayout = new QVBoxLayout();
    overallLayout->addLayout(m_formLayout);

    QHBoxLayout *btnHLayout = new QHBoxLayout();
    btnHLayout->addWidget(m_selectAppBtn);
    btnHLayout->addWidget(m_settingBtn);
    overallLayout->addLayout(btnHLayout);

    this->setLayout(overallLayout);
    this->resize(1024, 600);

    connect(m_selectAppBtn, &QPushButton::clicked, this, &MainWidget::onSelectAppBtnClicked);
    connect(m_settingBtn, &QPushButton::clicked, this, &MainWidget::onSettingBtnClicked);
}

void MainWidget::initSystemTray() {
{
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("://app.ico"));
    trayIcon->setVisible(true);

    QMenu *trayMenu = new QMenu(this);

    connect(trayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
            this->showNormal();
        }
    });

    connect(trayMenu->addAction(tr(u8"显示主界面")), &QAction::triggered, [=]() {
        this->showNormal();
    });

    connect(trayMenu->addAction(tr(u8"退出")), &QAction::triggered, [=]() {
        QCoreApplication::quit();
    });

    trayIcon->setContextMenu(trayMenu);
}
}

void MainWidget::updateAppInfo()
{
    auto appInfoMap = DatabaseManager::getInstance()->appInfoMap();

    // 遍历所有app的运行状态，更新最后一次启动时间
    for (auto it = appInfoMap->begin(); it != appInfoMap->end(); ++it) {
        if (isRunning(it->appName().toStdWString().c_str())) {
            // 计算运行时间
            qint64 currentTimeStamp = QDateTime::currentSecsSinceEpoch();

            if (it->isActiveFirstTime()) {
                it->setIsActiveFirstTime(false);
                it->setLastLaunchTime(currentTimeStamp);
            }
        }
    }
}

