#include "widget.h"

#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_dirPathLineEdit(nullptr),
      m_openDirBtn(nullptr),
      m_dealFileBtn(nullptr),
      m_targetDirBtn(nullptr),
      m_gridLayout(nullptr),
      m_dirPath(""),
      m_fileFilterRule(""),
      m_targetDirPath(""),
      m_allFilesList("")
{
    this->initView();

    connect(m_openDirBtn,   SIGNAL(clicked()), this, SLOT(onOpenDirBtnClicked()));
    connect(m_dealFileBtn,  SIGNAL(clicked()), this, SLOT(onDealFileBtnClicked()));
    connect(m_targetDirBtn, SIGNAL(clicked()), this, SLOT(onTargetBtnClicked()));
}

Widget::~Widget()
{

}

void Widget::onOpenDirBtnClicked()
{
    m_dirPath = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "C:",
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    m_dirPathLineEdit->setText(m_dirPath);
}

void Widget::onDealFileBtnClicked()
{
    if (m_dirPath.isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("The directory path is empty."));
        return;
    }

    QFileInfoList fileInfoList = this->getFilesList(m_dirPath);

    m_fileFilterRule = m_fileFilterLineEdit->text();
    if (m_fileFilterRule.isEmpty()) {
        QMessageBox::information(this, tr("INFO"), tr("File filter rule is empty."));
        return;
    }

    m_targetDirPath = m_dirPath + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");

    QDir targetDir;
    if(!targetDir.exists(m_targetDirPath)) {
        if (!targetDir.mkdir(m_targetDirPath))
            qDebug() << "Mkdir " + m_targetDirPath + " failed.";
        else
            qDebug() << "Mkdir " + m_targetDirPath + " successfully.";
    }

    //处理文件
    this->dealFiles(fileInfoList);
}

void Widget::onTargetBtnClicked()
{
    if (m_targetDirPath.isEmpty()) {
        QMessageBox::information(this, tr("INFO"), tr("The file has not been processed, "
                                                      "the destination path is empty."));
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(m_targetDirPath));
}

void Widget::initView()
{
    this->resize(600, 480);

    m_gridLayout = new QGridLayout(this);

    m_dirPathLineEdit = new QLineEdit(this);
    m_dirPathLineEdit->setEnabled(false);

    m_fileFilterLineEdit = new QLineEdit(this);
    m_fileFilterLineEdit->setPlaceholderText(tr("File filter rule..."));

    m_openDirBtn   = new QPushButton(tr("Open"),   this);
    m_dealFileBtn  = new QPushButton(tr("Deal"),   this);
    m_targetDirBtn = new QPushButton(tr("Target"), this);

    m_gridLayout->addWidget(m_dirPathLineEdit,    0, 0);
    m_gridLayout->addWidget(m_openDirBtn,         0, 1);
    m_gridLayout->addWidget(m_fileFilterLineEdit, 1, 0);
    m_gridLayout->addWidget(m_dealFileBtn,        1, 1);
    m_gridLayout->addWidget(m_targetDirBtn,       2, 1);
}

QFileInfoList Widget::getFilesList(const QString &dirPath)
{
    QDir dir(dirPath);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++) {
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = this->getFilesList(name);
        file_list.append(child_file_list);
    }

    return file_list;
}

void Widget::dealFiles(const QFileInfoList &fileInfoList)
{
    foreach (QFileInfo each, fileInfoList) {
        if (each.fileName().contains(m_fileFilterRule)) {
            qDebug() << each.absoluteFilePath();
            QFile::copy(each.absoluteFilePath(),
                        m_targetDirPath + "/" + each.fileName());
        }
    }
}

void Widget::copyFile(const QString &source, const QString &destination)
{

}
