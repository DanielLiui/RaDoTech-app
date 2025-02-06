#ifndef HISTORYTAB_H
#define HISTORYTAB_H

#include <QWidget>
#include <QDateTime>
#include "mainwindow.h"
#include "userdata.h"

namespace Ui {
class HistoryTab;
}

class HistoryTab : public QWidget {
    Q_OBJECT

public:
    explicit HistoryTab(QWidget *parent = nullptr);
    ~HistoryTab();
    void loadHistoryData(const QString& username);

private slots:
    void handleFilterApply();

private:
    Ui::HistoryTab *ui;
    QString currentUsername;
    
    void setupConnections();
    void setupTable();
    void updateHistoryTable(const QDateTime& start, const QDateTime& end);
    QString formatMeasurements(const QMap<QString, double>& measurements, const QString& prefix);
};

#endif // HISTORYTAB_H