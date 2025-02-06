#ifndef MEASUREMENTTAB_H
#define MEASUREMENTTAB_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QMap>
#include <QString>

namespace Ui {
class MeasurementTab;
}

struct MeasurementPoint {
    QString name;            // Point name (e.g., "H1 (Lung)")
    QString description;     // Anatomical description
    QString location;        // Body location
    QString imagePath;       // Path to reference image
    int number;             // Point number (1-24)
};

enum class ScanState {
    READY,          // Initial state, ready to start
    SCANNING,       // Actively scanning a point
    LIFT_PROBE,     // Need to lift probe after scan
    PLACE_PROBE     // Need to place probe for next scan
};

class MeasurementTab : public QWidget {
    Q_OBJECT

public:
    explicit MeasurementTab(QWidget *parent = nullptr);
    ~MeasurementTab();

signals:
    void measurementCompleted(const QMap<QString, double>& results);

private slots:
    void handleStartScan();
    void handleCancelScan();
    void handleActionButton();
    void updateMeasurementProgress();

private:
    Ui::MeasurementTab *ui;
    QTimer* scanTimer;
    int currentPoint;
    bool isMeasuring;
    ScanState currentState;
    QMap<int, MeasurementPoint> measurementPoints;
    QMap<QString, double> accumulatedResults;
    QMap<QString, QPixmap> imageCache;

    void setupConnections();
    void resetMeasurement();
    void initializeMeasurementPoints();
    void loadImages();
    void updateDisplay();
    void updateActionButton();
    void setState(ScanState newState);
    double simulateMeasurement();
    QString getInstructionText() const;
};

#endif