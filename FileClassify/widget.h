#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QLabel>
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
    void onTargetBtnClicked();

private:
    void initView();

    QFileInfoList getFilesList(const QString &dirPath);

    void dealFiles(const QFileInfoList &fileInfoList);

    void copyFile(const QString &source, const QString &destination);

private:
    QLineEdit   *m_dirPathLineEdit;
    QPushButton *m_openDirBtn;
    QLineEdit   *m_fileFilterLineEdit;
    QPushButton *m_dealFileBtn;
    QPushButton *m_targetDirBtn;
    QGridLayout *m_gridLayout;

    QString m_dirPath;
    QString m_fileFilterRule;
    QString m_targetDirPath;

    QStringList m_allFilesList;
};

#endif // WIDGET_H
