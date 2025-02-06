#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userselection.h"
#include "profiletab.h"
#include "historytab.h"
#include "measurementtab.h"
#include "resultstab.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentUser(nullptr)
    , batteryTimer(nullptr)  // Initialize to nullptr
    , batteryLevel(21)
{
    ui->setupUi(this);

    
    // Create battery timer
    ui->batteryLabel->setText("Battery: " + QString::number(batteryLevel));
    batteryTimer = new QTimer(this);
    batteryTimer->setInterval(60000); // 60 seconds FIXME: Should this be a global const passed through main?
    connect(batteryTimer, &QTimer::timeout,
            this, &MainWindow::checkBatteryStatus);
    
    // Create and add user selection page
    UserSelection* userSelection = new UserSelection;
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
    ui->stackedWidget->insertWidget(0, userSelection);

    
    // Initialize components
    initializeTabs();
    setupConnections();
    loadUsers();
    
    // Set initial state
    ui->stackedWidget->setCurrentIndex(0);
    setTabsEnabled(false);
    
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupConnections() 
{
    
    // Get user selection widget
    UserSelection* userSelection = qobject_cast<UserSelection*>(
        ui->stackedWidget->widget(0));
    
    if (userSelection) {
        connect(userSelection, &UserSelection::loginRequested,
                this, &MainWindow::handleLogin);
        connect(userSelection, &UserSelection::newUserAdded,
                this, &MainWindow::handleNewUser);
        connect(userSelection, &UserSelection::userDeleted,
                this, &MainWindow::handleUserDelete);
    }
    
    // Connect logout button
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &MainWindow::handleLogout);
            
    // Connect tab widget
    connect(ui->mainTabWidget, &QTabWidget::currentChanged,
            this, &MainWindow::handleTabChange);
            
}

void MainWindow::loadUsers() {
    QFile file("userdata.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open userdata.json for reading");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    QJsonArray usersArray = doc.array();

    users.clear();
    for (const QJsonValue &value : usersArray) {
        QJsonObject userObj = value.toObject();
        UserData userData = UserData::fromJson(userObj);
        users[userData.username] = userData;
    }
    
    // Update user list in selection page
    UserSelection* userSelection = findChild<UserSelection*>();
    if (userSelection) {
        userSelection->updateUserList(users.keys());
    }
}

void MainWindow::saveUsers() {
    QJsonArray usersArray;
    
    for (const auto& userData : users) {
        usersArray.append(userData.toJson());
    }
    
    QJsonDocument doc(usersArray);
    QFile file("userdata.json");
    
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Could not save user data");
        return;
    }
    
    file.write(doc.toJson());
}

void MainWindow::initializeTabs()
{
    
    // Create tabs
    ProfileTab* profileTab = new ProfileTab;
    MeasurementTab* measurementTab = new MeasurementTab;
    ResultsTab* resultsTab = new ResultsTab;
    HistoryTab* historyTab = new HistoryTab;
    
    // Add tabs
    ui->mainTabWidget->addTab(profileTab, "Profile");
    ui->mainTabWidget->addTab(measurementTab, "Measurement");
    ui->mainTabWidget->addTab(resultsTab, "Results");
    ui->mainTabWidget->addTab(historyTab, "History");
    
    // Connect signals
    connect(profileTab, &ProfileTab::profileUpdated,
            this, &MainWindow::handleProfileUpdate);
            
    connect(measurementTab, &MeasurementTab::measurementCompleted,
            this, &MainWindow::handleMeasurementCompleted);
}


void MainWindow::handleLogin(const QString& username, const QString& password)
{
    
    if (validateLogin(username, password)) {
        qDebug() << "Login successful";
        
        // Verify main page widgets exist
        if (!ui->mainTabWidget || !ui->currentUserLabel || !ui->batteryLabel) {
            qDebug() << "Critical error: Main page widgets not found!";
            return;
        }
        
        // Store user data
        currentUser = &users[username];
        
        // Update UI elements
        ui->currentUserLabel->setText("Current User: " + username);
        ui->batteryLabel->setText("Battery: " + QString::number(batteryLevel) + "%");
        
        // Enable components
        setTabsEnabled(true);
        
        // Load user data
        ProfileTab* profileTab = qobject_cast<ProfileTab*>(ui->mainTabWidget->widget(0));
        if (profileTab) {
            profileTab->loadUserData(*currentUser);
            qDebug() << "Loaded profile data";
        } else {
            qDebug() << "Warning: Profile tab not found!";
        }
        
        // Switch to main page and first tab
        ui->mainTabWidget->setCurrentIndex(0);
        qDebug() << "Set tab index to 0";
        
        ui->stackedWidget->setCurrentIndex(1);
        qDebug() << "Switched to main page";
        
        // Start battery monitoring
        if (batteryTimer) {
            batteryTimer->start();
        } else {
            qDebug() << "Error: Battery timer not available!";
        }
        
        qDebug() << "Login process complete";
    } else {
        QMessageBox::warning(this, "Login Failed",
                           "Invalid username or password");
    }
}

void MainWindow::handleLogout()
{

    
    if (batteryTimer) {
        batteryTimer->stop();
    }
    
    currentUser = nullptr;
    
    if (ui->stackedWidget) {
        ui->stackedWidget->setCurrentIndex(0);
    }
    
    setTabsEnabled(false);
    
    if (ui->currentUserLabel) {
        ui->currentUserLabel->clear();
    }

}

void MainWindow::handleTabChange(int index)
{
    if (!currentUser) {
        ui->mainTabWidget->setCurrentIndex(0);
        return;
    }

    switch (index) {
        case 0: { // Profile tab
            ProfileTab* profileTab = qobject_cast<ProfileTab*>(
                ui->mainTabWidget->widget(0));
            if (profileTab) {
                profileTab->loadUserData(*currentUser);
            }
            break;
        }
        case 1: { // Measurement tab
            break;
        }
        case 2: { // Results tab
            break;
        }
        case 3: { // History tab
            HistoryTab* historyTab = qobject_cast<HistoryTab*>(
                ui->mainTabWidget->widget(3));
            if (historyTab) {
                historyTab->loadHistoryData(currentUser->username);
            }
            break;
        }
    }
}

void MainWindow::handleProfileUpdate(const UserData& userData) {
    if (!currentUser) return;
    UserData updatedData = userData;
    updatedData.password = currentUser->password;
    
    // Update current user data
    users[updatedData.username] = updatedData;
    *currentUser = updatedData;
    
    // Save to JSON
    saveUsers();
}

void MainWindow::handleNewUser(const QString& username, const QString& password) {
    // Validate inputs
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Invalid username or password");
        return;
    }

    // Check maximum users
    if (users.size() >= 5) {
        QMessageBox::warning(this, "Error", "Maximum number of users reached");
        return;
    }
    
    // Check if user already exists
    if (users.contains(username)) {
        QMessageBox::warning(this, "Error", "Username already exists");
        return;
    }
    
    try {
        // Create new user data
        UserData userData;
        userData.username = username;
        userData.password = password;  // Store password
        
        // Add to users map
        users[username] = userData;
        
        // Save to file
        saveUsers();
        
        // Update user selection list
        UserSelection* userSelection = qobject_cast<UserSelection*>(
            ui->stackedWidget->widget(0));
        if (userSelection) {
            userSelection->updateUserList(users.keys());
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", 
            QString("Failed to create user: %1").arg(e.what()));
    }
}

void MainWindow::handleUserDelete(const QString& username) {
    if (users.contains(username)) {
        users.remove(username);
        saveUsers();
        
        if (currentUser && currentUser->username == username) {
            handleLogout();
        }
    }
}

void MainWindow::setTabsEnabled(bool enabled)
{
    qDebug() << "Setting tabs enabled:" << enabled;
    
    if (!ui || !ui->mainTabWidget) {
        qDebug() << "Error: Main tab widget not available!";
        return;
    }
    
    // Enable/disable main tab widget
    ui->mainTabWidget->setEnabled(enabled);
    
    // Enable/disable logout button if it exists
    if (ui->logoutButton) {
        ui->logoutButton->setEnabled(enabled);
    }
    
    // Enable/disable individual tabs
    for (int i = 0; i < ui->mainTabWidget->count(); ++i) {
        ui->mainTabWidget->setTabEnabled(i, enabled);
        QWidget* tab = ui->mainTabWidget->widget(i);
        if (tab) {
            tab->setEnabled(enabled);
        }
    }
}

bool MainWindow::validateLogin(const QString& username, const QString& password) {
    //Check if user exists
    if (!users.contains(username)) {
        return false;
    }
    
    return users[username].password == password;
}

void MainWindow::checkBatteryStatus()
{
    qDebug() << "Checking battery status";
    
    if (!ui || !ui->batteryLabel) {
        qDebug() << "Battery label not available!";
        return;
    }
    
    // Simulate battery drain
    batteryLevel = std::max(0, batteryLevel - 1);
    
    // Update battery label
    QString batteryText = "Battery: " + QString::number(batteryLevel) + "%";
    ui->batteryLabel->setText(batteryText);
    
    // Handle low battery conditions
    if (batteryLevel <= 20 && batteryLevel > 5) {
        QMessageBox::warning(this, "Low Battery",
            "Battery level is low (" + QString::number(batteryLevel) + "%). Please charge soon.");
    }
    else if (batteryLevel <= 5 && batteryLevel > 0) {
        QMessageBox::critical(this, "Critical Battery",
            "Battery critically low. Device will shut down soon.");
    }
    else if (batteryLevel <= 0) {
        QMessageBox::critical(this, "Shutting Down",
            "Battery depleted. Shutting down.");
        handleLogout();
        close();
        return;
    }
}

void MainWindow::updateBatteryStatus(int level) {
    QString batteryText = "Battery: " + QString::number(level) + "%";
    ui->batteryLabel->setText(batteryText);
}

void MainWindow::handleMeasurementCompleted(const QMap<QString, double>& results) {
    if (!currentUser) {
        qWarning() << "No user logged in, measurement data will be lost";
        return;
    }

    // Add measurement to user's history
    currentUser->addMeasurement(results);
    
    // Update user data in the map
    users[currentUser->username] = *currentUser;
    
    // Save to file
    saveUsers();

    // Update results tab
    ResultsTab* resultsTab = qobject_cast<ResultsTab*>(
        ui->mainTabWidget->widget(2));
    if (resultsTab) {
        resultsTab->displayResults(results);
    }

    // Refresh history tab if it's open
    HistoryTab* historyTab = qobject_cast<HistoryTab*>(
        ui->mainTabWidget->widget(3));
    if (historyTab) {
        historyTab->loadHistoryData(currentUser->username);
    }
}

