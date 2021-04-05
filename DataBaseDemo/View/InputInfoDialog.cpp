#include "InputInfoDialog.h"
#include "ui_InputInfoDialog.h"
#include <QPalette>
#include <QMessageBox>

#include <QDebug>

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

    QStringList kingdoms;
    kingdoms << tr("魏国") << tr("蜀国") << tr("吴国") << tr("群雄");
    ui->comboBoxKingdoms->addItems(kingdoms);

    ui->frame->setStyleSheet("QLabel {"
                                 "font-size: 18px;"
                                 "color: white;"
                             "}"
                             "QLabel#labelTitle {"
                                 "font-size: 26px;"
                                 "color: white;"
                             "}");

    this->setFixedSize(850 ,370);

    //输入框设置默认提示
    ui->lineEditID->setPlaceholderText(tr("必填"));
    ui->lineEditName->setPlaceholderText(tr("必填"));

}

InputInfoDialog::~InputInfoDialog()
{
    delete ui;
}

void InputInfoDialog::onBtnConfirmClicked()
{
    //检查必填项是否已填写
    if (ui->lineEditID->text().isEmpty() ||
            ui->lineEditName->text().isEmpty()) {
        QMessageBox::critical(this, tr("错误"), tr("必填项未填写"));

        return;
    }

    HeroInfo heroInfo;

    heroInfo.setId(ui->lineEditID->text().toInt());
    heroInfo.setName(ui->lineEditName->text());
    heroInfo.setStyleName(ui->lineEditStyleName->text());

    switch (ui->comboBoxKingdoms->currentIndex()) {
    case 0: heroInfo.setFaction("魏国"); break;
    case 1: heroInfo.setFaction("蜀国"); break;
    case 2: heroInfo.setFaction("吴国"); break;
    case 3: heroInfo.setFaction("群雄"); break;
    default:
        break;
    }

    heroInfo.setPosition(ui->lineEditPosition->text());
    heroInfo.setMount(ui->lineEditMount->text());
    heroInfo.setWeapon(ui->lineEditWeapon->text());
    heroInfo.setBirthAndDeathTime(ui->lineEditBirthAndDeathTime->text());
    heroInfo.setPosthumounsTitle(ui->lineEditPosthumousTitle->text());
    heroInfo.setTips(ui->lineEditTips->text());

    //保存数据
    this->accept();

    emit dataReady(heroInfo);
}

void InputInfoDialog::onBtnCancelClicked()
{
    this->close();
}
