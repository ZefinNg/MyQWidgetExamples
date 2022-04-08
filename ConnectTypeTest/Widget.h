#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QThread>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onBtnAutoClicked();
    void onBtnDirectClicked();
    void onBtnQueuedClicked();
    void onBtnBlockClicked();
    void onBtnUniqueClicked();

private:
    QPushButton *m_btnAutoConnect;
    QPushButton *m_btnDirectConnect;
    QPushButton *m_btnQueuedConnect;
    QPushButton *m_btnBlockConnect;
    QPushButton *m_btnUniqueConnect;

    int m_autoSlotInvokedTimes;
    int m_directSlotInvokedTimes;
    int m_queuedSlotInvokedTimes;
    int m_blockSlotInvokedTimes;
    int m_uniqueSlotInvokedTimes;

    QTextBrowser *m_debugBrowser;

    Qt::HANDLE m_mainThreadId;
    Qt::HANDLE m_subThreadId;
};
#endif // WIDGET_H
