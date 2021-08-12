#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPalette>
#include <QBrush>
#include "Controllers/MainWidgetController.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onSwtichButtonClicked(bool isChecked);
    void onPrintOathButtonClicked();
    void onPrintData2ButtonClicked();
    void onPrintCopyWritingButtonClicked();

    void onPrintTimerTimeout();

private:
    void fillOathData();
    void filleCopywritingData();

    void checkPrintCondition();
    bool configHorizontalMagnification();
    bool configVerticalMagnification();
    void configRotationAngle();
    void configAntiWhite();

private:
    Ui::MainWidget *ui;

    MainWidgetController *m_mainWidgetController;
    QStringList m_readyPrintDataList;
    QTimer m_printTimer;
};

#endif // MAINWIDGET_H
