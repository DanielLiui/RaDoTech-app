#include "historytab.h"
#include "ui_historytab.h"
#include "mainwindow.h"
#include <QMessageBox>

HistoryTab::HistoryTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryTab)
{
    ui->setupUi(this);
    setupConnections();
    
    // Initialize date range
    QDate currentDate = QDate::currentDate();
    ui->startDateEdit->setDate(currentDate.addMonths(-1));
    ui->endDateEdit->setDate(currentDate.addDays(1));

    // Setup table
    setupTable();
}

HistoryTab::~HistoryTab()
{
    delete ui;
}

void HistoryTab::setupTable()
{
    // Set column widths
    ui->historyTable->setColumnWidth(0, 100);  // Date
    ui->historyTable->setColumnWidth(1, 80);   // Time
    ui->historyTable->setColumnWidth(2, 70);   // Score
    ui->historyTable->setColumnWidth(3, 150);  // Left Hand
    ui->historyTable->setColumnWidth(4, 150);  // Right Hand
    ui->historyTable->setColumnWidth(5, 150);  // Left Foot
    ui->historyTable->setColumnWidth(6, 150);  // Right Foot

    // Enable word wrap
    ui->historyTable->setWordWrap(true);
    ui->historyTable->setAlternatingRowColors(true);
    ui->historyTable->verticalHeader()->setDefaultSectionSize(60);
}

void HistoryTab::setupConnections()
{
    connect(ui->applyFilterButton, &QPushButton::clicked,
            this, &HistoryTab::handleFilterApply);
}

void HistoryTab::handleFilterApply()
{
    QDateTime startDate = ui->startDateEdit->dateTime();
    QDateTime endDate = ui->endDateEdit->dateTime();
    
    if (startDate > endDate) {
        QMessageBox::warning(this, "Invalid Date Range",
                           "Start date must be before end date");
        return;
    }

    updateHistoryTable(startDate, endDate);
}

QString HistoryTab::formatMeasurements(const QMap<QString, double>& measurements, 
                                     const QString& prefix)
{
    QString result;
    QString side = prefix.endsWith("R") ? "R" : "L";  // Determine which side we're formatting
    
    // Remove the side indicator from prefix
    QString basePrefix = prefix;
    basePrefix.remove(QRegExp("[LR]$"));
    
    for (int i = 1; i <= 6; ++i) {
        if (!result.isEmpty()) result += "\n";
        
        // Construct the measurement key (e.g., "H1L" or "F2R")
        QString pointKey = QString("%1%2%3").arg(basePrefix).arg(i).arg(side);
        
        // Get the measurement value, default to 0.0 if not found
        double value = measurements.value(pointKey, 0.0);
        
        // Format the output string
        result += QString("%1%2: %3").arg(basePrefix).arg(i).arg(value, 0, 'f', 1);
    }
    return result;
}

void HistoryTab::updateHistoryTable(const QDateTime& start, const QDateTime& end)
{
    ui->historyTable->setRowCount(0);

    MainWindow* mainWindow = qobject_cast<MainWindow*>(window()->window());
    if (!mainWindow) return;

    const UserData* userData = mainWindow->getCurrentUser();
    if (!userData) return;

    // Add each measurement within the date range
    for (const auto& record : userData->measurementHistory) {
        if (record.timestamp >= start && record.timestamp <= end) {
            int row = ui->historyTable->rowCount();
            ui->historyTable->insertRow(row);
            
            // Add date
            ui->historyTable->setItem(row, 0, 
                new QTableWidgetItem(record.timestamp.date().toString("yyyy-MM-dd")));
            
            // Add time
            ui->historyTable->setItem(row, 1, 
                new QTableWidgetItem(record.timestamp.time().toString("hh:mm")));
            
            // Add score
            ui->historyTable->setItem(row, 2, 
                new QTableWidgetItem(QString::number(record.overallScore, 'f', 1)));
            
            // Add measurements by group
            ui->historyTable->setItem(row, 3, 
                new QTableWidgetItem(formatMeasurements(record.measurements, "HL"))); // Left Hand
            ui->historyTable->setItem(row, 4, 
                new QTableWidgetItem(formatMeasurements(record.measurements, "HR"))); // Right Hand
            ui->historyTable->setItem(row, 5, 
                new QTableWidgetItem(formatMeasurements(record.measurements, "FL"))); // Left Foot
            ui->historyTable->setItem(row, 6, 
                new QTableWidgetItem(formatMeasurements(record.measurements, "FR"))); // Right Foot
        }
    }

    // Adjust row heights to content
    for (int row = 0; row < ui->historyTable->rowCount(); ++row) {
        ui->historyTable->resizeRowToContents(row);
    }
}

void HistoryTab::loadHistoryData(const QString& username)
{
    currentUsername = username;
    ui->historyTable->setRowCount(0);
    handleFilterApply();
}