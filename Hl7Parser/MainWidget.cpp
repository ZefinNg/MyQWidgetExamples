#include "MainWidget.h"
#include <QGridLayout>
#include <QTableWidgetItem>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_textEdit(new QTextEdit(this)),
      m_tableWidget(new QTableWidget(this)),
      m_parserBtn(new QPushButton("解析", this))
{
    //TableWidget
    QStringList elementNameList;
    elementNameList << "ID集" << "值类型" << "观察识别符" << "观察ID" << "观察值"
                    << "单位" << "参考值范围" << "不正常的标记" << "概率" << "异常检查的特点"
                    << "观察结果状态" << "最后一次正常值记录时间" << "用户定义通路核对" << "观察日期/时间" << "生产者ID"
                    << "观察负责人" << "观察方法" << "设备识别符" << "分析日期/时间";
    m_tableWidget->setColumnCount(elementNameList.size());
    m_tableWidget->setHorizontalHeaderLabels(elementNameList);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(m_textEdit, 0, 0, 1, 3);
    gridLayout->addWidget(m_tableWidget, 1, 0, 1, 3);
    gridLayout->addWidget(m_parserBtn, 2, 1, 1, 1);

    this->setLayout(gridLayout);

    connect(m_parserBtn, SIGNAL(clicked()), this, SLOT(onParserBtnClicked()));
}

MainWidget::~MainWidget()
{

}

void MainWidget::onParserBtnClicked()
{
    QString hl7Text = m_textEdit->toPlainText();
    if (hl7Text.isEmpty())
        return;

    m_tableWidget->setRowCount(m_tableWidget->rowCount()+1);
    QStringList fieldList = hl7Text.split("|");
    for (int i = 1; i < fieldList.size(); ++i) {
        QTableWidgetItem *eachItem = new QTableWidgetItem(fieldList.at(i));
        m_tableWidget->setItem(m_tableWidget->rowCount()-1, i-1, eachItem);
    }
}
