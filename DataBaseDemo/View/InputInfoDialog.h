#ifndef INPUTINFODIALOG_H
#define INPUTINFODIALOG_H

#include <QDialog>
#include "Domains/HeroInfo.h"

namespace Ui {
class InputInfoDialog;
}

class InputInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputInfoDialog(QWidget *parent = 0);
    ~InputInfoDialog();

signals:
    void dataReady(HeroInfo heroInfo);

private slots:
    void onBtnConfirmClicked();
    void onBtnCancelClicked();

private:
    Ui::InputInfoDialog *ui;
};

#endif // INPUTINFODIALOG_H
