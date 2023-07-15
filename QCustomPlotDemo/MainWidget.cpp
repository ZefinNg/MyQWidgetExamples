#include "MainWidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <cmath>
#include <QApplication>
#include <functional>

#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    m_customPlot = new QCustomPlot(this);

    m_drawBtn       = new QPushButton(tr("Draw"), this);
    m_clearBtn      = new QPushButton(tr("Clear"), this);
    m_dragCheckBox  = new QCheckBox(tr("Drag"), this);
    m_zoomCheckBox  = new QCheckBox(tr("Zoom"), this);
    m_addIdentifierBtn = new QPushButton(tr("AddIdentifier"), this);

    QHBoxLayout *toolHLayout = new QHBoxLayout();
    toolHLayout->addWidget(m_drawBtn);
    toolHLayout->addWidget(m_clearBtn);
    toolHLayout->addWidget(m_dragCheckBox);
    toolHLayout->addWidget(m_zoomCheckBox);
    toolHLayout->addWidget(m_addIdentifierBtn);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addLayout(toolHLayout, 0, 0);
    gridLayout->addWidget(m_customPlot);

    this->resize(600, 400);

    connect(m_drawBtn,  SIGNAL(clicked()), this, SLOT(onDrawBtnClicked()));
    connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(onClearBtnClicked()));
    connect(m_dragCheckBox, SIGNAL(clicked(bool)), this, SLOT(onDragCheckBoxClicked(bool)));
    connect(m_zoomCheckBox, SIGNAL(clicked(bool)), this, SLOT(onZoomCheckBoxClicked(bool)));
    connect(m_addIdentifierBtn, SIGNAL(clicked()), this, SLOT(onAddIdentifierBtnClicked()));
}

MainWidget::~MainWidget()
{

}

void MainWidget::onDrawBtnClicked()
{
#if 0
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
#else
    int n = 500;
    double phase = 0;
    double k = 3;
    QVector<double> x(n), y(n);
    for (int i=0; i<n; ++i)
    {
      x[i] = i/(double)(n-1)*34 - 17;
      y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
    }

    QCPGraph *graph = m_customPlot->addGraph();
    graph->setData(x, y);
    graph->setPen(QPen(Qt::blue));
    graph->rescaleKeyAxis();
    m_customPlot->yAxis->setRange(-1.45, 1.65);
    m_customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);

    //标注点的文本
    // add label for phase tracer:

    m_customPlot->replot();
#endif
}

void MainWidget::onClearBtnClicked()
{
    m_customPlot->clearGraphs();
    m_customPlot->clearItems();
    m_customPlot->replot();
}

void MainWidget::onDragCheckBoxClicked(bool isChecked)
{
#if 0
    QCP::Interactions flag = m_customPlot->interactions();
    if (isChecked)
        m_customPlot->setInteractions(flag | QCP::iRangeDrag);
    else
        m_customPlot->setInteraction(QCP::iRangeDrag, false);
#else
    if (isChecked)
        m_customPlot->setInteraction(QCP::iRangeDrag, true);
    else
        m_customPlot->setInteraction(QCP::iRangeDrag, false);
#endif
}

void MainWidget::onZoomCheckBoxClicked(bool isChecked)
{
#if 0
    QCP::Interactions flag = m_customPlot->interactions();
    if (isChecked)
        m_customPlot->setInteractions(flag | QCP::iRangeZoom);
    else
        m_customPlot->setInteraction(QCP::iRangeZoom, false);
#else
    if (isChecked)
        m_customPlot->setInteraction(QCP::iRangeZoom, true);
    else
        m_customPlot->setInteraction(QCP::iRangeZoom, false);
#endif
}

void MainWidget::onAddIdentifierBtnClicked()
{
    IdentifierInfoDialog indentifierWidget;
    if (QDialog::Accepted == indentifierWidget.exec()) {
        IdentifierInfo identifierInfo = indentifierWidget.getIdentifierInfo();
        this->addIdentifierInfo(identifierInfo);
    }
    else {

    }
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

void MainWidget::addIdentifierInfo(IdentifierInfo info)
{
    switch (info.type()) {
    case IdentifierInfo::Arrow: {
        QCPItemTracer *phaseTracer = new QCPItemTracer(m_customPlot);
        phaseTracer->setGraph(m_customPlot->graph());
//        phaseTracer->setGraphKey((M_PI*1.5-0)/3);
        phaseTracer->setGraphKey(0);
        phaseTracer->setInterpolating(true);
        phaseTracer->setStyle(QCPItemTracer::tsCircle);
        phaseTracer->setPen(QPen(Qt::red));
        phaseTracer->setBrush(Qt::red);
        phaseTracer->setSize(7);

        QCPItemText *phaseTracerText = new QCPItemText(m_customPlot);
        phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
        phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
        phaseTracerText->position->setCoords(1.0, 0.95); // lower right corner of axis rect
        phaseTracerText->setText("Points of fixed\nphase define\nphase velocity vp");
        phaseTracerText->setTextAlignment(Qt::AlignLeft);
        phaseTracerText->setFont(QFont(font().family(), 9));
        phaseTracerText->setPadding(QMargins(8, 0, 0, 0));

        QCPItemCurve *phaseTracerArrow = new QCPItemCurve(m_customPlot);
        phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);
        phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
        phaseTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
        phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
        phaseTracerArrow->end->setCoords(10, 10);
        phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
        phaseTracerArrow->endDir->setCoords(30, 30);
        phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
        phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPosition().y()-phaseTracerText->top->pixelPosition().y())*0.85));
    }
        break;
    case IdentifierInfo::Packet: {
        QCPItemBracket *bracket = new QCPItemBracket(m_customPlot);
        bracket->setStyle((QCPItemBracket::BracketStyle)info.bracketStyle());
        bracket->left->setCoords(info.xStartCoord(), info.yStartCoord());
        bracket->right->setCoords(info.xEndCoord(), info.yEndCoord());
        bracket->setLength(10);

        QCPItemText *wavePacketText = new QCPItemText(m_customPlot);
        wavePacketText->position->setParentAnchor(bracket->center);
        wavePacketText->position->setCoords(0, -10); // move 10 pixels to the top from bracket center anchor
        wavePacketText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        wavePacketText->setText(info.text());
        wavePacketText->setFont(QFont(font().family(), 10));
    }
        break;
    default:
        break;
    }

    m_customPlot->replot();
}
