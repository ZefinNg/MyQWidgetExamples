#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onParserBtnClicked();

private:
    QTextEdit *m_textEdit;
    QTableWidget *m_tableWidget;
    QPushButton *m_parserBtn;
};

#endif // MAINWIDGET_H
