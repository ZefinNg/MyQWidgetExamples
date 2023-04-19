#ifndef IDENTIFIERINFODIALOG_H
#define IDENTIFIERINFODIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include "IdentifierInfo.h"

class IdentifierInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit IdentifierInfoDialog(QWidget *parent = nullptr);

    IdentifierInfo getIdentifierInfo();

signals:

public slots:

private slots:
    void onConfirmBtnClicked();
    void onCancelBtnClicked();

private:
    QLabel *m_infoLabel;
    QLineEdit *m_infoLineEdit;
    QLabel *m_xCoordLabel;
    QDoubleSpinBox *m_xCoordSpinBox;
    QLabel *m_yCoordLabel;
    QDoubleSpinBox *m_yCoordSpinBox;
    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
};

#endif // IDENTIFIERINFODIALOG_H
