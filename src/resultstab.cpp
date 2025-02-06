#include "resultstab.h"
#include "ui_resultstab.h"
#include <QMessageBox>
#include <QDateTime>
#include <QtMath>
#include <QString>
#include <QMap>

ResultsTab::ResultsTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResultsTab)
{
    ui->setupUi(this);
    
    if (ui->metricsPlot) {
        delete ui->metricsPlot;
    }
    
    setupMetricsPlot();
    setupConnections();
}

ResultsTab::~ResultsTab()
{
    delete ui;
}

void ResultsTab::setupMetricsPlot()
{
    // Create QCustomPlot widget
    metricsPlot = new QCustomPlot();
    ui->metricsLayout->addWidget(metricsPlot);

    // Configure plot appearance
    metricsPlot->setBackground(QBrush(QColor(240, 240, 240)));
    
    // Setup axes
    metricsPlot->xAxis->setLabel("Meridian points");
    metricsPlot->yAxis->setLabel("Ryodoraku value(μA)");
    metricsPlot->yAxis->setRange(0, 200);
    
    // Configure grid
    metricsPlot->xAxis->grid()->setVisible(true);
    metricsPlot->yAxis->grid()->setVisible(true);
    metricsPlot->xAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::SolidLine));
    metricsPlot->yAxis->grid()->setPen(QPen(QColor(200, 200, 200), 1, Qt::SolidLine));
    
    // Enable interactions
    metricsPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    
    // Setup legend
    metricsPlot->legend->setVisible(true);
    metricsPlot->legend->setFont(QFont("MS Shell Dlg 2", 8));
    metricsPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 230)));
    
    // Position legend in top right
    metricsPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
}

void ResultsTab::setupConnections()
{
}

void ResultsTab::displayResults(const QMap<QString, double>& results)
{
    currentResults = results;

    // Update scan time
    QString currentTime = QDateTime::currentDateTime()
                         .toString("yyyy-MM-dd hh:mm:ss");
    ui->scanTimeLabel->setText(currentTime);

    // Update visualizations
    updateMetricsPlot(results);
    updateRecommendations(results);
}

void ResultsTab::updateMetricsPlot(const QMap<QString, double>& results)
{
    //This is loosely based on the ideas in the PDFs given
    if (results.isEmpty()) return;

    // Clear previous graphs
    metricsPlot->clearGraphs();

    // Prepare data vectors
    QVector<double> x, yLeft, yRight;
    QStringList points = {"H1", "H2", "H3", "H4", "H5", "H6",
                         "F1", "F2", "F3", "F4", "F5", "F6"};
    QStringList pointOrgans = {"Lung", "Pericardium", "Heart", "Small \nintestine", "Lymph \nvessel", "Large \nintestine",
                         "Spleen/\npancreas", "Liver", "Kidney and \nAdrenal glands", "Bladder", "Gall \nbladder", "Stomach"};

    // Populate data vectors
    for (int i = 0; i < points.size(); ++i) {
        x.append(i);
        yLeft.append(results.value(points[i] + "L", 0));
        yRight.append(results.value(points[i] + "R", 0));
    }

    // Calculate physiological range
    double meanValue = calculatePhysiologicalMean(results);
    double upperLimit = meanValue + 14;
    double lowerLimit = meanValue - 14;

    // Create graph for left side measurements
    QCPGraph *leftGraph = metricsPlot->addGraph();
    leftGraph->setName("Left Side");
    leftGraph->setData(x, yLeft);
    leftGraph->setPen(QPen(Qt::blue, 2));
    leftGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 7));
    leftGraph->setLineStyle(QCPGraph::lsLine);

    // Create graph for right side measurements
    QCPGraph *rightGraph = metricsPlot->addGraph();
    rightGraph->setName("Right Side");
    rightGraph->setData(x, yRight);
    rightGraph->setPen(QPen(Qt::red, 2));
    rightGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 7));
    rightGraph->setLineStyle(QCPGraph::lsLine);

    // Add physiological range lines
    QCPGraph *upperLine = metricsPlot->addGraph();
    upperLine->setName("Normal upper Limit");
    QVector<double> upperX = {x.first(), x.last()};
    QVector<double> upperY = {upperLimit, upperLimit};
    upperLine->setData(upperX, upperY);
    upperLine->setPen(QPen(Qt::darkGreen, 1, Qt::DashLine));

    QCPGraph *lowerLine = metricsPlot->addGraph();
    lowerLine->setName("Normal lower Limit");
    QVector<double> lowerY = {lowerLimit, lowerLimit};
    lowerLine->setData(upperX, lowerY);
    lowerLine->setPen(QPen(Qt::darkGreen, 1, Qt::DashLine));

    // Configure axes
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    for (int i = 0; i < points.size(); ++i) {
        textTicker->addTick(i, pointOrgans[i]);
    }
    metricsPlot->xAxis->setTicker(textTicker);
    metricsPlot->xAxis->setRange(-0.5, points.size() - 0.5);
    
    // Set y-axis range to match screenshot
    double yMin = qMin(0.0, qMin(lowerLimit * 0.9, *std::min_element(yLeft.begin(), yLeft.end())));
    double yMax = qMax(125.0, qMax(upperLimit * 1.1, *std::max_element(yLeft.begin(), yLeft.end())));
    metricsPlot->yAxis->setRange(yMin, yMax);

    // Setup y-axis ticks
    QSharedPointer<QCPAxisTicker> yTicker(new QCPAxisTicker);
    yTicker->setTickCount(6); // Adjust this value to match the screenshot
    metricsPlot->yAxis->setTicker(yTicker);

    // Refresh plot
    metricsPlot->replot();
}

double ResultsTab::calculatePhysiologicalMean(const QMap<QString, double>& results)
{
    if (results.isEmpty()) return 0.0;

    double sum = 0.0;
    int count = 0;

    for (auto it = results.begin(); it != results.end(); ++it) {
        sum += it.value();
        count++;
    }

    return count > 0 ? sum / count : 0.0;
}

void ResultsTab::updateRecommendations(const QMap<QString, double>& results)
{
    QString recommendations = generateRecommendations(results);
    ui->recommendationsText->setText(recommendations);
}


QString ResultsTab::generateRecommendations(const QMap<QString, double>& results) {
    QString recommendations;
    
    // Calculate mean value     
    double mean = 0.0;
    int count = 0;
    for (auto value : results.values()) {
        mean += value;
        count++;
    }
    mean = count > 0 ? mean / count : 0.0;
    
    // Define physiological range (from the paper)
    double upperLimit = mean + 14;
    double lowerLimit = mean - 14;
    
    // Set tracks given recommendations
    QSet<QString> givenRecommendations;
    
    //helperto add recommendations without duplicates
    auto addRecommendation = [&recommendations, &givenRecommendations](const QString& rec) {
        if (!givenRecommendations.contains(rec)) {
            recommendations += rec + "\n";
            //givenRecommendations.insert(rec);
        }
    };
    
    //helper function to check bilateral readings
    auto checkBilateralPoint = [&](const QString& basePoint) {
        double leftValue = results.value(basePoint + "L", 0.0);
        double rightValue = results.value(basePoint + "R", 0.0);
        
        // If either side is out of range, return the higher variance sid
        if (leftValue > upperLimit || rightValue > upperLimit) {
            return 1;  // Elevated
        } else if (leftValue < lowerLimit || rightValue < lowerLimit) {
            return -1; // Decreased
        }
        return 0;     // Normal
    };
    
    // Analyze lung meridian (H1)
    int h1Status = checkBilateralPoint("H1");
    if (h1Status > 0) {
        addRecommendation("Above normal lung reading indicates you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    } else if (h1Status < 0) {
        addRecommendation("Below normal lung reading indicates you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    }
    
    // Analyze heart meridian (H2 and H3 together)
    bool heartElevated = false;
    bool heartDecreased = false;

    for (QString point : {"H2", "H3"}) {
        int status = checkBilateralPoint(point);
        if (status > 0) heartElevated = true;
        if (status < 0) heartDecreased = true;
    }
    
    if (heartElevated) {
        addRecommendation("Above normal pericardium/heart readings indicate you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    } else if (heartDecreased) {
        addRecommendation("Below normal pericardium/heart readings indicate you may be experiencing:");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    }
    
    // Analyze digestive system (F1 and F6 together)
    bool digestiveElevated = false;
    bool digestiveDecreased = false;
    
    for (QString point : {"F1", "F6"}) {
        int status = checkBilateralPoint(point);
        if (status > 0) digestiveElevated = true;
        if (status < 0) digestiveDecreased = true;
    }
    
    if (digestiveElevated) {
        addRecommendation("Above normal stomach/spleen reading suggests you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    } else if (digestiveDecreased) {
        addRecommendation("Below normal stomach/spleen reading indicates you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    }
    
    // Analyze kidney meridian (F3)
    int f3Status = checkBilateralPoint("F3");
    if (f3Status > 0) {
        addRecommendation("Above normal kidney reading suggests you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    } else if (f3Status < 0) {
        addRecommendation("Below normal kidney reading indicates you may be experiencing: ");
        addRecommendation("- Symptom 1");
        addRecommendation("- Symptom 2");
        addRecommendation("- ...");
        addRecommendation("\nRecommendations: ");
        addRecommendation("- ...\n");
    }
    
    return recommendations.isEmpty() ? 
        "All readings are within normal physiological range. Well done!" :
        recommendations;
}
