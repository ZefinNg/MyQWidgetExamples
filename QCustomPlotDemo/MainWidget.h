#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include "QCustomPlot/qcustomplot.h"
#include "IdentifierInfoDialog.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onDrawBtnClicked();
    void onClearBtnClicked();
    void onDragCheckBoxClicked(bool isChecked);
    void onZoomCheckBoxClicked(bool isChecked);
    void onAddIdentifierBtnClicked();

private:
    bool parseCSVFile(QVector<double>& xValue, QVector<double>& yValue, const QString& filePath);

    void addIdentifierInfo(IdentifierInfo info);

private:
    QCustomPlot *m_customPlot;

    QPushButton *m_drawBtn;
    QPushButton *m_clearBtn;
    QCheckBox *m_dragCheckBox;
    QCheckBox *m_zoomCheckBox;

    QPushButton *m_addIdentifierBtn;
};

#endif // MAINWIDGET_H
