#include "InputInfoDialog.h"
#include "ui_InputInfoDialog.h"
#include <QPalette>
#include <QMessageBox>

#include <QDebug>

#define WEI_KINGDOM   "The Wei Kingdom"
#define SHU_KINGDOM   "The Shu Kingdom"
#define WU_KINGDOM    "The Wu Kingdom"
#define OTHER_KINGDOM "The Other Kingdom"

InputInfoDialog::InputInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputInfoDialog)
{
    ui->setupUi(this);

    this->initView();

    QList<QLabel *> labelList = this->findChildren<QLabel *>();
    foreach (QLabel *each, labelList) {
        each->setWordWrap(true);
    }
}

InputInfoDialog::InputInfoDialog(HeroInfo heroInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputInfoDialog)
{
    ui->setupUi(this);

    this->initView();

    if (heroInfo.faction() == WEI_KINGDOM)
        ui->comboBoxKingdoms->setCurrentIndex(WEI);
    else if (heroInfo.faction() == SHU_KINGDOM)
        ui->comboBoxKingdoms->setCurrentIndex(SHU);
    else if (heroInfo.faction() == WU_KINGDOM)
        ui->comboBoxKingdoms->setCurrentIndex(WU);
    else
        ui->comboBoxKingdoms->setCurrentIndex(OTHER);

    ui->lineEditName->setText(heroInfo.name());
    ui->lineEditStyleName->setText(heroInfo.styleName());
    ui->lineEditPosition->setText(heroInfo.position());

    ui->lineEditMount->setText(heroInfo.mount());
    ui->lineEditWeapon->setText(heroInfo.weapon());
    ui->lineEditBirthAndDeathTime->setText(heroInfo.birthAndDeathTime());
    ui->lineEditPosthumousTitle->setText(heroInfo.posthumounsTitle());

    ui->lineEditAllusion->setText(heroInfo.allusion());
    ui->lineEditTips->setText(heroInfo.tips());
}

InputInfoDialog::~InputInfoDialog()
{
    delete ui;
}

void InputInfoDialog::onBtnConfirmClicked()
{
    //检查Required项是否已填写
    if (ui->lineEditName->text().isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("Required fields are not filled."));

        return;
    }

    HeroInfo heroInfo;

    heroInfo.setName(ui->lineEditName->text());
    heroInfo.setStyleName(ui->lineEditStyleName->text());

    switch (ui->comboBoxKingdoms->currentIndex()) {
    case 0:  heroInfo.setFaction(WEI_KINGDOM);    break;
    case 1:  heroInfo.setFaction(SHU_KINGDOM);    break;
    case 2:  heroInfo.setFaction(WU_KINGDOM);     break;
    case 3:
    default: heroInfo.setFaction(OTHER_KINGDOM);  break;
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

void InputInfoDialog::initView()
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/Resources/Images/HerosInfo.jpg")));
    this->setPalette(palette);

    connect(ui->btnConfirm, SIGNAL(clicked()), this, SLOT(onBtnConfirmClicked()));
    connect(ui->btnCancel,  SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

    QStringList kingdoms;
    kingdoms << tr("The Wei Kingdom") << tr("The Shu Kingdom") << tr("The Wu Kingdom") << tr("The other Kingdoms");
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

    //输入框设置默认Tips
    ui->lineEditName->setPlaceholderText(tr("Required"));
}
