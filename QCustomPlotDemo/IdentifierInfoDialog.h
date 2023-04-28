#ifndef IDENTIFIERINFODIALOG_H
#define IDENTIFIERINFODIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
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
    void onTypeBoxChanged(int index);
    void onConfirmBtnClicked();
    void onCancelBtnClicked();

private:
    QLabel *m_typeLabel;
    QComboBox *m_typeComboBox;

    QLabel *m_styleLabel;
    QComboBox *m_styleComboBox;

    QLabel *m_infoLabel;
    QLineEdit *m_infoLineEdit;

    QLabel *m_startPointLabel;
    QLabel *m_xStartCoordLabel;
    QDoubleSpinBox *m_xStartCoordSpinBox;
    QLabel *m_yStartCoordLabel;
    QDoubleSpinBox *m_yStartCoordSpinBox;

    QLabel *m_endPoint;
    QLabel *m_xEndCoordLabel;
    QDoubleSpinBox *m_xEndCoordSpinBox;
    QLabel *m_yEndCoordLabel;
    QDoubleSpinBox *m_yEndCoordSpinBox;

    QPushButton *m_confirmBtn;
    QPushButton *m_cancelBtn;
};

#endif // IDENTIFIERINFODIALOG_H
