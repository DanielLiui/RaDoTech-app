#ifndef RESULTSTAB_H
#define RESULTSTAB_H

#include <QWidget>
#include <QMap>
#include <qcustomplot.h>
#include "userdata.h"

namespace Ui {
class ResultsTab;
}

class ResultsTab : public QWidget {
    Q_OBJECT

public:
    explicit ResultsTab(QWidget *parent = nullptr);
    ~ResultsTab();
    void displayResults(const QMap<QString, double>& results);

private:
    Ui::ResultsTab *ui;
    QCustomPlot* metricsPlot;
    QMap<QString, double> currentResults;
    
    void setupConnections();
    void setupMetricsPlot();
    void updateMetricsPlot(const QMap<QString, double>& results);
    void updateRecommendations(const QMap<QString, double>& results);
    QString generateRecommendations(const QMap<QString, double>& results);
    double calculatePhysiologicalMean(const QMap<QString, double>& results);
};

#endif // RESULTSTAB_H