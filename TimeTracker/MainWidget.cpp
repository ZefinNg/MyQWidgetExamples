#include "MainWidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QStandardPaths>

#include <windows.h>
#include <tlhelp32.h>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
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
    m_formLayout = new QFormLayout();
    m_appLabel = new QLabel(this);
    m_timeLabel = new QLabel(this);
    m_formLayout->addRow(m_appLabel, m_timeLabel);

    m_selectAppBtn = new QPushButton(tr(u8"选择软件"), this);
    m_trackerTimer = new QTimer(this);
    m_trackerTimer->setInterval(1000 * 60);

    QVBoxLayout *overallLayout = new QVBoxLayout();
    overallLayout->addLayout(m_formLayout);
    overallLayout->addWidget(m_selectAppBtn);

    this->setLayout(overallLayout);

    connect(m_selectAppBtn, &QPushButton::clicked, this, &MainWidget::onSelectAppBtnClicked);
    connect(m_trackerTimer, &QTimer::timeout, this, &MainWidget::onTrackerTimer);
#endif
}

MainWidget::~MainWidget()
{

}

bool MainWidget::isRunning(const wchar_t* processName)
{
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(processEntry);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &processEntry))
    {
        do
        {
            if (wcscmp(processEntry.szExeFile, processName) == 0)
            {
                CloseHandle(snapshot);
                return true;
            }
        } while (Process32Next(snapshot, &processEntry));
    }
    CloseHandle(snapshot);
    return false;
}

void MainWidget::onSelectAppBtnClicked()
{
    QFileInfo fileInfo(QFileDialog::getOpenFileName(this, tr(u8"选择软件"),
                                                QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                tr("Applicantion (*.exe)")));
    qDebug() << __FUNCTION__ << __LINE__ << fileInfo.fileName();
    if (fileInfo.fileName().isEmpty())
        return;
    else {
        m_trackerApplication = fileInfo.fileName();
        m_appLabel->setText(m_trackerApplication);
        if (isRunning(m_trackerApplication.toStdWString().c_str())) {
            m_startTime = QDateTime::currentDateTime();
            qDebug() << __FUNCTION__ << __LINE__ << "Start Time:" << m_startTime;
        }
        m_trackerTimer->start();
    }
}

void MainWidget::onTrackerTimer()
{
    if (isRunning(m_trackerApplication.toStdWString().c_str())) {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        qDebug() << __FUNCTION__ << __LINE__ << "Current Time:" << currentDateTime;
        auto deltaSecs = m_startTime.msecsTo(currentDateTime) / 1000;
        qDebug() << __FUNCTION__ << __LINE__ << deltaSecs;
        auto minutes = deltaSecs / 60;
        auto hours = minutes / 60;
        QString timeString = QString(u8"%1时%2分").arg(hours).arg(minutes%60);
        m_timeLabel->setText(timeString);
    }
    else {
        qDebug() << __FUNCTION__ << __LINE__ << "未检测到程序正在运行:" << m_trackerApplication;
    }
}
