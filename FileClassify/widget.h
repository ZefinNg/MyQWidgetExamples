#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>

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

    void copyFile(const QString &source, const QString &destination);

private:
    QLineEdit   *m_fileFilterLineEdit;
    QPushButton *m_openDirBtn;
    QPushButton *m_dealFileBtn;
    QHBoxLayout *m_gridLayout;

    QString m_dirPath;
};

#endif // WIDGET_H
