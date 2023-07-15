#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QTimer>
#include <QDateTime>

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
    void onTrackerTimer();

private:
    QFormLayout *m_formLayout;
    QPushButton *m_selectAppBtn;
    QLabel *m_appLabel;
    QLabel *m_timeLabel;
    QTimer *m_trackerTimer;
    QString m_trackerApplication;
    QDateTime m_startTime;
};

#endif // MAINWIDGET_H
