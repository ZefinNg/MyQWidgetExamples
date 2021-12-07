#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onOpenDirBtnClicked();
    void onDealFileBtnClicked();

private:
    void initView();

private:
    QLineEdit   *m_fileFilterLineEdit;
    QPushButton *m_openDirBtn;
    QPushButton *m_dealFileBtn;
    QHBoxLayout *m_gridLayout;
};

#endif // WIDGET_H
