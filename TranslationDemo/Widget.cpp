#include "Widget.h"
#include "ui_Widget.h"
#include <QGridLayout>
#include <QApplication>
#include <QDebug>
#include "GlobalText.h"

extern QTranslator *g_translator;
extern GlobalText globalText;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_label(NULL),
    m_languageComboBox(NULL),
    m_translator(NULL),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_label = new QLabel(tr("Example of Qt dynamic language switching.")+globalText.langToken(), this);
    m_languageComboBox = new QComboBox(this);

    QStringList languageList;
    languageList << "English" << "中文" << "русский язык";
    m_languageComboBox->addItems(languageList);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(m_label);
    gridLayout->addWidget(m_languageComboBox);

    connect(m_languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onLanguageChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onLanguageChanged(int languageIndex)
{
//    if (g_translator != NULL) {
//        qApp->removeTranslator(g_translator);
//        delete g_translator;
//        g_translator = NULL;
//    }
//    g_translator = new QTranslator(qApp);

//    QString qmPath;
//    switch (languageIndex) {
//    case CH_ZN:
//        qmPath = QApplication::applicationDirPath()+"/zh_CN.qm";
//        break;
//    case EN:
//        qmPath = QApplication::applicationDirPath()+"/ru_RU.qm";
//        break;
//    case RU:
//        qmPath = QApplication::applicationDirPath()+"/en.qm";
//        break;
//    default:
//        break;
//    }

//    g_translator->load(qmPath);
//    qApp->installTranslator(g_translator);

//    ui->retranslateUi(this);
    emit globalText.changeLang(languageIndex);
}
