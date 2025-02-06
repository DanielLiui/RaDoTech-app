#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTimer>
#include "userdata.h"

class ProfileTab;
class MeasurementTab;
class ResultsTab;
class HistoryTab;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    const UserData* getCurrentUser() const { return currentUser; }

private slots:
    void handleLogin(const QString& username, const QString& password);
    void handleLogout();
    void handleTabChange(int index);
    void handleProfileUpdate(const UserData& userData);
    void handleNewUser(const QString& username, const QString& password);
    void handleUserDelete(const QString& username);
    void handleMeasurementCompleted(const QMap<QString, double>& results);
    void updateBatteryStatus(int level);
    void checkBatteryStatus();

private:
    Ui::MainWindow *ui;
    QMap<QString, UserData> users;
    UserData* currentUser;
    QTimer* batteryTimer;
    int batteryLevel;

    void setupConnections();
    void loadUsers();
    void saveUsers();
    void initializeTabs();
    void setTabsEnabled(bool enabled);
    bool validateLogin(const QString& username, const QString& password);
};

#endif // MAINWINDOW_H