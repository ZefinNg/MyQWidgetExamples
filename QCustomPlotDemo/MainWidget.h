#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "QCustomPlot/qcustomplot.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onDrawBtnClicked();

private:
     bool parseCSVFile(QVector<double>& xValue, QVector<double>& yValue, const QString& filePath);

private:
    QCustomPlot *m_customPlot;
    QPushButton *m_drawBtn;

};

#endif // MAINWIDGET_H
