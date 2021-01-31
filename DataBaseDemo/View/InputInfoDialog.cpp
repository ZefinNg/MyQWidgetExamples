#include "InputInfoDialog.h"
#include "ui_InputInfoDialog.h"
#include <QPalette>

InputInfoDialog::InputInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputInfoDialog)
{
    ui->setupUi(this);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/Images/HerosInfo.jpg")));
    this->setPalette(palette);

    connect(ui->btnConfirm, SIGNAL(clicked()), this, SLOT(onBtnConfirmClicked()));
    connect(ui->btnCancel,  SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));
}

InputInfoDialog::~InputInfoDialog()
{
    delete ui;
}

void InputInfoDialog::onBtnConfirmClicked()
{
    HeroInfo heroInfo;

    heroInfo.setId(ui->lineEditID->text().toInt());
    heroInfo.setName(ui->lineEditName->text());
    heroInfo.setStyleName(ui->lineEditStyleName->text());
    heroInfo.setFaction(ui->lineEditFaction->text());
    heroInfo.setPosition(ui->lineEditPosition->text());
    heroInfo.setMount(ui->lineEditMount->text());
    heroInfo.setWeapon(ui->lineEditWeapon->text());
    heroInfo.setBirthAndDeathTime(ui->lineEditBirthAndDeathTime->text());
    heroInfo.setPosthumounsTitle(ui->lineEditPosthumousTitle->text());
    heroInfo.setTips(ui->lineEditTips->text());

    //保存数据
    this->close();

    emit dataReady(heroInfo);
}

void InputInfoDialog::onBtnCancelClicked()
{
    this->close();
}
