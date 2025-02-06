#include "measurementtab.h"
#include "ui_measurementtab.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>

MeasurementTab::MeasurementTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MeasurementTab)
    , currentPoint(0)
    , isMeasuring(false)
    , currentState(ScanState::READY)
    , scanTimer(nullptr)
{
    ui->setupUi(this);
    setupConnections();
    initializeMeasurementPoints();
    loadImages();
    updateDisplay();
}

MeasurementTab::~MeasurementTab()
{
    if (scanTimer) {
        scanTimer->stop();
        delete scanTimer;
    }
    delete ui;
}

void MeasurementTab::initializeMeasurementPoints()
{
    // Left Hand Points (H1-H6)
    measurementPoints[0] = {"H1 (Lung)", 
        "First finger on palm side along radius to armpit",
        "Left hand, palm side", 
        "./images/handfront_left.png", 1};
    measurementPoints[1] = {"H2 (Pericardium)", 
        "Third finger on palm side, inferior line of forearm",
        "Left hand, palm side", 
        "./images/handfront_left.png", 2};
    measurementPoints[2] = {"H3 (Heart)", 
        "Fifth finger on palm side along ulna",
        "Left hand, palm side", 
        "./images/handfront_left.png", 3};
    measurementPoints[3] = {"H4 (Small intestine)", 
        "Fifth finger on back hand side along ulna",
        "Left hand, back side", 
        "./images/handback_left.png", 4};
    measurementPoints[4] = {"H5 (Lymph vessel)", 
        "Fourth finger on back hand side center",
        "Left hand, back side", 
        "./images/handback_left.png", 5};
    measurementPoints[5] = {"H6 (Large intestine)", 
        "Second finger on back hand side along radius",
        "Left hand, back side", 
        "./images/handback_left.png", 6};

    // Right Hand Points (H1-H6)
    measurementPoints[6] = {"H1 (Lung)", 
        "First finger on palm side along radius to armpit",
        "Right hand, palm side", 
        "./images/handfront_right.png", 7};
    measurementPoints[7] = {"H2 (Pericardium)", 
        "Third finger on palm side, inferior line of forearm",
        "Right hand, palm side", 
        "./images/handfront_right.png", 8};
    measurementPoints[8] = {"H3 (Heart)", 
        "Fifth finger on palm side along ulna",
        "Right hand, palm side", 
        "./images/handfront_right.png", 9};
    measurementPoints[9] = {"H4 (Small intestine)", 
        "Fifth finger on back hand side along ulna",
        "Right hand, back side", 
        "./images/handback_right.png", 10};
    measurementPoints[10] = {"H5 (Lymph vessel)", 
        "Fourth finger on back hand side center",
        "Right hand, back side", 
        "./images/handback_right.png", 11};
    measurementPoints[11] = {"H6 (Large intestine)", 
        "Second finger on back hand side along radius",
        "Right hand, back side", 
        "./images/handback_right.png", 12};

    // Left Foot Points (F1-F6)
    measurementPoints[12] = {"F1 (Spleen)", 
        "Inner side of first toe",
        "Left foot", 
        "./images/foot_right.png", 13};
    measurementPoints[13] = {"F2 (Liver)", 
        "Between first and second toe",
        "Left foot", 
        "./images/foot_right.png", 14};
    measurementPoints[14] = {"F3 (Kidney)", 
        "Center of sole",
        "Left foot", 
        "./images/foot_right.png", 15};
    measurementPoints[15] = {"F4 (Bladder)", 
        "Outer tip of fifth toe",
        "Left foot", 
        "./images/foot_right.png", 16};
    measurementPoints[16] = {"F5 (Gall bladder)", 
        "Outer tip of fourth toe",
        "Left foot", 
        "./images/foot_right.png", 17};
    measurementPoints[17] = {"F6 (Stomach)", 
        "Second and third toe",
        "Left foot", 
        "./images/foot_right.png", 18};

    // Right Foot Points (F1-F6)
    measurementPoints[18] = {"F1 (Spleen)", 
        "Inner side of first toe",
        "Right foot", 
        "./images/foot_right.png", 19};
    measurementPoints[19] = {"F2 (Liver)", 
        "Between first and second toe",
        "Right foot", 
        "./images/foot_right.png", 20};
    measurementPoints[20] = {"F3 (Kidney)", 
        "Center of sole",
        "Right foot", 
        "./images/foot_right.png", 21};
    measurementPoints[21] = {"F4 (Bladder)", 
        "Outer tip of fifth toe",
        "Right foot", 
        "./images/foot_right.png", 22};
    measurementPoints[22] = {"F5 (Gall bladder)", 
        "Outer tip of fourth toe",
        "Right foot", 
        "./images/foot_right.png", 23};
    measurementPoints[23] = {"F6 (Stomach)", 
        "Second and third toe",
        "Right foot", 
        "./images/foot_right.png", 24};
}

void MeasurementTab::loadImages()
{
    QStringList imagePaths = {
        "./images/handfront_left.png",
        "./images/handback_left.png",
        "./images/handfront_right.png",
        "./images/handback_right.png",
        "./images/foot_right.png"
    };

    for (const QString& path : imagePaths) {
        QPixmap img(path);
        if (!img.isNull()) {
            imageCache[path] = img;
        } else {
            qWarning() << "Failed to load image:" << path;
        }
    }
}

void MeasurementTab::setupConnections()
{
    connect(ui->startScanButton, &QPushButton::clicked,
            this, &MeasurementTab::handleStartScan);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &MeasurementTab::handleCancelScan);
    connect(ui->actionButton, &QPushButton::clicked,
            this, &MeasurementTab::handleActionButton);
}

void MeasurementTab::handleStartScan()
{
    if (isMeasuring) return;

    isMeasuring = true;
    currentPoint = 0;
    ui->measurementProgress->setValue(0);
    ui->startScanButton->setEnabled(false);
    ui->cancelButton->setEnabled(true);
    accumulatedResults.clear();
    setState(ScanState::PLACE_PROBE);
    updateDisplay();
}

void MeasurementTab::handleCancelScan()
{
    if (!isMeasuring) return;
    
    if (scanTimer) {
        scanTimer->stop();
        delete scanTimer;
        scanTimer = nullptr;
    }
    
    resetMeasurement();
    QMessageBox::information(this, "Scan Cancelled", "Measurement scan has been cancelled");
}

void MeasurementTab::handleActionButton()
{
    switch (currentState) {
        case ScanState::PLACE_PROBE:
            // Start scanning this point
            setState(ScanState::SCANNING);
            scanTimer = new QTimer(this);
            connect(scanTimer, &QTimer::timeout, this, &MeasurementTab::updateMeasurementProgress);
            scanTimer->setSingleShot(true);  // Ensure timer only fires once
            scanTimer->start(1500);
            break;
            
        case ScanState::LIFT_PROBE:
            // Prepare for next point
            if (currentPoint >= 24) {
                emit measurementCompleted(accumulatedResults);
                resetMeasurement();
                QMessageBox::information(this, "Scan Complete", 
                    "Measurement scan completed successfully");
            } else {
                setState(ScanState::PLACE_PROBE);
            }
            break;
            
        default:
            break;
    }
    
    updateDisplay();
}

void MeasurementTab::updateMeasurementProgress()
{
    if (!isMeasuring || currentState != ScanState::SCANNING) return;

    // Calculate progress
    int progress = ((currentPoint + 1) * 100) / 24;
    ui->measurementProgress->setValue(progress);

    // Get current measurement point
    const auto& point = measurementPoints[currentPoint];
    
    // Simulate measurement and store result
    double measurementValue = simulateMeasurement();
    
    // Create point identifier
    QString pointId;
    if (currentPoint < 6) {
        pointId = QString("H%1L").arg(currentPoint + 1);
    } else if (currentPoint < 12) {
        pointId = QString("H%1R").arg(currentPoint - 5);
    } else if (currentPoint < 18) {
        pointId = QString("F%1L").arg(currentPoint - 11);
    } else {
        pointId = QString("F%1R").arg(currentPoint - 17);
    }
    
    // Store measurement
    accumulatedResults[pointId] = measurementValue;

    // Clean up timer
    scanTimer->deleteLater();
    scanTimer = nullptr;
    
    currentPoint++;
    setState(ScanState::LIFT_PROBE);
    updateDisplay();
}

void MeasurementTab::setState(ScanState newState)
{
    currentState = newState;
    updateActionButton();
}

void MeasurementTab::updateActionButton()
{
    switch (currentState) {
        case ScanState::READY:
            ui->actionButton->setVisible(false);
            break;
            
        case ScanState::SCANNING:
            ui->actionButton->setVisible(false);
            ui->actionButton->setEnabled(false);
            break;
            
        case ScanState::LIFT_PROBE:
            ui->actionButton->setText("Lift Probe");
            ui->actionButton->setVisible(true);
            ui->actionButton->setEnabled(true);
            break;
            
        case ScanState::PLACE_PROBE:
            ui->actionButton->setText("Place Probe");
            ui->actionButton->setVisible(true);
            ui->actionButton->setEnabled(true);
            break;
    }
}

QString MeasurementTab::getInstructionText() const
{
    if (!isMeasuring) {
        return "Press Start to begin measurement";
    }

    const auto& point = measurementPoints[currentPoint];
    QString baseText = QString("Point %1/24:\n%2\n%3\n%4")
        .arg(currentPoint + 1)
        .arg(point.name)
        .arg(point.location)
        .arg(point.description);

    switch (currentState) {
        case ScanState::SCANNING:
            return baseText + "\n\nScanning in progress... Please hold the probe steady.";
            
        case ScanState::LIFT_PROBE:
            return baseText + "\n\nScan complete. Please lift the probe from this position.";
            
        case ScanState::PLACE_PROBE:
            return baseText + "\n\nPlace the probe at the indicated position and press 'Place Probe' to begin scanning.";
            
        default:
            return baseText;
    }
}

void MeasurementTab::updateDisplay()
{
    ui->instructionLabel->setText(getInstructionText());

    if (isMeasuring) {
        const auto& point = measurementPoints[currentPoint];
        if (imageCache.contains(point.imagePath)) {
            QPixmap scaledImage = imageCache[point.imagePath].scaled(
                ui->placeholderLabel->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            );
            ui->placeholderLabel->setPixmap(scaledImage);
        }
    } else {
        ui->placeholderLabel->clear();
    }
}

void MeasurementTab::resetMeasurement()
{
    isMeasuring = false;
    currentPoint = 0;
    currentState = ScanState::READY;
    accumulatedResults.clear();
    ui->measurementProgress->setValue(0);
    ui->startScanButton->setEnabled(true);
    ui->cancelButton->setEnabled(false);
    updateActionButton();
    updateDisplay();
}

double MeasurementTab::simulateMeasurement()
{
    // Generate random value between 50 and 200
    int range = 90;  // Range of random values
    int randomValue = QRandomGenerator::global()->bounded(range);
    return 50.0 + randomValue;  // Shift range to start at 50
}