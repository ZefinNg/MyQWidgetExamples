#include "IdentifierInfoDialog.h"
#include <QHBoxLayout>
#include "float.h"

IdentifierInfoDialog::IdentifierInfoDialog(QWidget *parent) : QDialog(parent)
{
    m_typeLabel = new QLabel(tr("Type:"), this);
    m_typeComboBox = new QComboBox(this);
    m_typeComboBox->addItem(tr("Arrow"));
    m_typeComboBox->addItem(tr("Packet"));

    m_styleLabel = new QLabel(tr("Style:"), this);
    m_styleComboBox = new QComboBox(this);
    m_styleComboBox->addItem(tr("Square"));
    m_styleComboBox->addItem(tr("Round"));
    m_styleComboBox->addItem(tr("Curly"));
    m_styleComboBox->addItem(tr("Calligraphic"));

    m_infoLabel     = new QLabel(tr("Text:"), this);
    m_infoLineEdit  = new QLineEdit(this);

    m_startPointLabel    = new QLabel(tr("startPoint:"), this);
    m_xStartCoordLabel   = new QLabel(tr("X:"), this);
    m_xStartCoordSpinBox = new QDoubleSpinBox(this);
    m_xStartCoordSpinBox->setMinimum(-DBL_MAX);
    m_yStartCoordLabel   = new QLabel(tr("Y:"), this);
    m_yStartCoordSpinBox = new QDoubleSpinBox(this);

    m_endPoint         = new QLabel(tr("endPoint:"), this);
    m_xEndCoordLabel   = new QLabel(tr("X:"), this);
    m_xEndCoordSpinBox = new QDoubleSpinBox(this);
    m_yEndCoordLabel   = new QLabel(tr("Y:"), this);
    m_yEndCoordSpinBox = new QDoubleSpinBox(this);

    m_confirmBtn    = new QPushButton(tr("Confirm"), this);
    m_cancelBtn     = new QPushButton(tr("Cancel"), this);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(m_styleLabel, 0, 0, 1, 2);
    gridLayout->addWidget(m_styleComboBox, 0, 2, 1, 3);

    gridLayout->addWidget(m_infoLabel, 1, 0, 1, 2);
    gridLayout->addWidget(m_infoLineEdit, 1, 2, 1, 3);

    gridLayout->addWidget(m_startPointLabel, 2, 0);
    gridLayout->addWidget(m_xStartCoordLabel, 2, 1);
    gridLayout->addWidget(m_xStartCoordSpinBox, 2, 2);
    gridLayout->addWidget(m_yStartCoordLabel, 2, 3);
    gridLayout->addWidget(m_yStartCoordSpinBox, 2, 4);

    gridLayout->addWidget(m_endPoint, 3, 0);
    gridLayout->addWidget(m_xEndCoordLabel, 3, 1);
    gridLayout->addWidget(m_xEndCoordSpinBox, 3, 2);
    gridLayout->addWidget(m_yEndCoordLabel, 3, 3);
    gridLayout->addWidget(m_yEndCoordSpinBox, 3, 4);

    QHBoxLayout *yesNoBtnLayout = new QHBoxLayout();
    yesNoBtnLayout->addWidget(m_confirmBtn);
    yesNoBtnLayout->addWidget(m_cancelBtn);
    gridLayout->addLayout(yesNoBtnLayout, 4, 0, 1, 5);

    connect(m_typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onTypeBoxChanged(int)));
    connect(m_confirmBtn, SIGNAL(clicked()), this, SLOT(onConfirmBtnClicked()));
    connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
}

IdentifierInfo IdentifierInfoDialog::getIdentifierInfo()
{
    IdentifierInfo identifierInfo;
    identifierInfo.setBracketStyle(m_styleComboBox->currentIndex());
    identifierInfo.setText(m_infoLineEdit->text());
    identifierInfo.setXStartCoord(m_xStartCoordSpinBox->value());
    identifierInfo.setYStartCoord(m_yStartCoordSpinBox->value());
    identifierInfo.setXEndCoord(m_xEndCoordSpinBox->value());
    identifierInfo.setYEndCoord(m_yEndCoordSpinBox->value());

    return identifierInfo;
}

void IdentifierInfoDialog::onTypeBoxChanged(int index)
{
    switch (index) {
    case 0:
        break;
    case 1:
        break;
    default:
        qDebug() << "Unkown index.";
        break;
    }
}

void IdentifierInfoDialog::onConfirmBtnClicked()
{
    this->accept();
}

void IdentifierInfoDialog::onCancelBtnClicked()
{
    this->reject();
}
