#include "IdentifierInfoDialog.h"
#include <QHBoxLayout>

IdentifierInfoDialog::IdentifierInfoDialog(QWidget *parent) : QDialog(parent)
{
    m_infoLabel     = new QLabel(tr("Text:"), this);
    m_infoLineEdit  = new QLineEdit(this);
    m_xCoordLabel   = new QLabel(tr("X:"), this);
    m_xCoordSpinBox = new QDoubleSpinBox(this);
    m_yCoordLabel   = new QLabel(tr("Y:"), this);
    m_yCoordSpinBox = new QDoubleSpinBox(this);
    m_confirmBtn    = new QPushButton(tr("Confirm"), this);
    m_cancelBtn     = new QPushButton(tr("Cancel"), this);

    QHBoxLayout *infoHBoxLayout = new QHBoxLayout();
    infoHBoxLayout->addWidget(m_infoLabel);
    infoHBoxLayout->addWidget(m_infoLineEdit);
    infoHBoxLayout->addWidget(m_xCoordLabel);
    infoHBoxLayout->addWidget(m_xCoordSpinBox);
    infoHBoxLayout->addWidget(m_yCoordLabel);
    infoHBoxLayout->addWidget(m_yCoordSpinBox);

    QHBoxLayout *yesNoHBoxLayout = new QHBoxLayout();
    yesNoHBoxLayout->addWidget(m_confirmBtn);
    yesNoHBoxLayout->addWidget(m_cancelBtn);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addLayout(infoHBoxLayout, 0, 0);
    gridLayout->addLayout(yesNoHBoxLayout, 1, 0);

    connect(m_confirmBtn, SIGNAL(clicked()), this, SLOT(onConfirmBtnClicked()));
    connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
}

IdentifierInfo IdentifierInfoDialog::getIdentifierInfo()
{
    IdentifierInfo identifierInfo;
    identifierInfo.setText(m_infoLineEdit->text());
    identifierInfo.setXCoord(m_xCoordSpinBox->value());
    identifierInfo.setYCoord(m_yCoordSpinBox->value());

    return identifierInfo;
}

void IdentifierInfoDialog::onConfirmBtnClicked()
{
    this->accept();
}

void IdentifierInfoDialog::onCancelBtnClicked()
{
    this->reject();
}
