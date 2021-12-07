#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_fileFilterLineEdit(nullptr),
      m_openDirBtn(nullptr),
      m_dealFileBtn(nullptr),
      m_gridLayout(nullptr)
{
    this->initView();

    connect(m_openDirBtn,  SIGNAL(clicked()), this, SLOT(onOpenDirBtnClicked()));
    connect(m_dealFileBtn, SIGNAL(clicked()), this, SLOT(onDealFileBtnClicked()));
}

Widget::~Widget()
{

}

void Widget::onOpenDirBtnClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "C:",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    m_fileFilterLineEdit->setText(dir);
}

void Widget::onDealFileBtnClicked()
{

}

void Widget::initView()
{
    this->resize(600, 480);

    m_gridLayout         = new QHBoxLayout(this);

    m_fileFilterLineEdit = new QLineEdit(this);
    m_fileFilterLineEdit->setEnabled(false);

    m_openDirBtn         = new QPushButton(tr("Open"), this);
    m_dealFileBtn        = new QPushButton(tr("Deal"), this);

    m_gridLayout->addWidget(m_fileFilterLineEdit);
    m_gridLayout->addWidget(m_openDirBtn);
    m_gridLayout->addWidget(m_dealFileBtn);
}
