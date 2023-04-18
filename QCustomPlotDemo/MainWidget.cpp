#include "MainWidget.h"
#include <QGridLayout>
#include <cmath>
#include <QApplication>
#include <functional>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_customPlot = new QCustomPlot(this);
    m_drawBtn = new QPushButton(tr("Draw"), this);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(m_drawBtn);
    gridLayout->addWidget(m_customPlot);

    this->resize(600, 400);

    connect(m_drawBtn, SIGNAL(clicked()), this, SLOT(onDrawBtnClicked()));
}

MainWidget::~MainWidget()
{

}

void MainWidget::onDrawBtnClicked()
{
    QString filePath = QCoreApplication::applicationDirPath() + "\\TestFile\\202302200005.csv";
    QVector<double> xValue, yValue;

    if (!this->parseCSVFile(xValue, yValue, filePath)) {
        qInfo() << "Failed to parse " << filePath;
        return;
    }

    m_customPlot->clearGraphs();
    m_customPlot->addGraph();
    int xAxisRange = static_cast<int>(*std::max_element(xValue.begin(), xValue.end()));
    int yAxisRange = static_cast<int>(*std::max_element(yValue.begin(), yValue.end()));
    m_customPlot->xAxis->setRange(0, xAxisRange+50);
    m_customPlot->yAxis->setRange(-yAxisRange, yAxisRange);

    m_customPlot->graph(0)->addData(xValue, yValue);

    QVector<double> negateYValue(yValue.size());
    std::transform(yValue.begin(), yValue.end(), negateYValue.begin(), std::negate<double>());

    m_customPlot->addGraph();
    m_customPlot->graph(1)->addData(xValue, negateYValue);
    m_customPlot->replot();
}

bool MainWidget::parseCSVFile(QVector<double> &xValue, QVector<double> &yValue, const QString &filePath)
{
    QFile csvFile(filePath);
    if (!csvFile.open(QIODevice::ReadOnly)) {
        qInfo() << "Failed to open " << filePath;
        return false;
    }

    QTextStream readStream(&csvFile);
    QString eachLine = readStream.readLine();
    while (!eachLine.isNull()) {
        if (eachLine.contains(",") && eachLine.split(",").count() >= 2) {
            double x = eachLine.split(",").at(0).toDouble();
            double y = eachLine.split(",").at(1).toDouble();

            if (std::isnormal(x) == 1) {
                xValue.append(x);
                yValue.append(y);
            }
        }
        eachLine = readStream.readLine();
    }

    csvFile.close();
    return true;
}
