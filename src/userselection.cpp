#include "userselection.h"
#include "ui_userselection.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

UserSelection::UserSelection(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserSelection)
{
    ui->setupUi(this);
    setupUI();
}

UserSelection::~UserSelection()
{
    delete ui;
}

void UserSelection::setupUI() {
    qDebug() << "Setting up UserSelection UI";
    
    // Add password field
    passwordField = new QLineEdit(this);
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setPlaceholderText("Enter Password");
    
    // Insert password field after user list
    QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(layout());
    if (mainLayout) {
        mainLayout->insertWidget(mainLayout->indexOf(ui->userListWidget) + 1,
                               passwordField);
    }
    
    // Connect buttons with debug output
    connect(ui->addUserButton, &QPushButton::clicked,
            this, [this]() {
                qDebug() << "Add user button clicked";
                handleAddUser();
            });
            
    connect(ui->deleteUserButton, &QPushButton::clicked,
            this, [this]() {
                qDebug() << "Delete user button clicked";
                handleDeleteUser();
            });
            
    connect(ui->selectUserButton, &QPushButton::clicked,
            this, [this]() {
                qDebug() << "Select user button clicked";
                handleSelectUser();
            });
            
    qDebug() << "UserSelection UI setup complete";
}

void UserSelection::updateUserList(const QStringList& usernames) {
    // If it's a single username, add it to the existing list
    if (usernames.size() == 1 && ui->userListWidget->count() > 0) {
        if (ui->userListWidget->findItems(usernames[0], Qt::MatchExactly).isEmpty()) {
            ui->userListWidget->addItem(usernames[0]);
        }
    } else {
        // Otherwise, replace the entire list
        ui->userListWidget->clear();
        ui->userListWidget->addItems(usernames);
    }
}

void UserSelection::handleAddUser() {
    if (ui->userListWidget->count() >= 5) {
        QMessageBox::warning(this, "Error", 
            "Maximum number of users (5) reached. Please delete a user before adding new one.");
        return;
    }

    bool ok;
    QString username;
    do {
        username = QInputDialog::getText(this, "New User",
            "Enter username (minimum 3 characters):", QLineEdit::Normal, "", &ok);
        
        if (!ok) return;

        // Validate username
        if (username.length() < 3) {
            QMessageBox::warning(this, "Invalid Username", 
                "Username must be at least 3 characters long.");
            continue;
        }
        if (ui->userListWidget->findItems(username, Qt::MatchExactly).count() > 0) {
            QMessageBox::warning(this, "Error", "Username already exists");
            continue;
        }

        break;
    } while (true);

    QString password;
    do {
        password = QInputDialog::getText(this, "New User",
            "Enter password (minimum 6 characters):", QLineEdit::Password, "", &ok);
        
        if (!ok) return;

        // Validate password
        if (password.length() < 6) {
            QMessageBox::warning(this, "Invalid Password", 
                "Password must be at least 6 characters long.");
            continue;
        }

        break;
    } while (true);

    QString confirmPassword = QInputDialog::getText(this, "New User",
        "Confirm password:", QLineEdit::Password, "", &ok);
    
    if (!ok) return;

    if (confirmPassword != password) {
        QMessageBox::warning(this, "Error", "Passwords do not match");
        return;
    }

    emit newUserAdded(username, password);

    updateUserList(QStringList(username));
    
    QMessageBox::information(this, "Success", 
        QString("User '%1' created successfully").arg(username));
}

void UserSelection::handleDeleteUser() {
    QListWidgetItem* currentItem = ui->userListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Error", "Please select a user to delete");
        return;
    }

    QString username = currentItem->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
        "Are you sure you want to delete user '" + username + "'?",
        QMessageBox::Yes | QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        emit userDeleted(username);
        delete ui->userListWidget->takeItem(ui->userListWidget->row(currentItem));
    }
}

void UserSelection::handleSelectUser() {
    qDebug() << "Handling user selection";
    
    QListWidgetItem* currentItem = ui->userListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "Error", "Please select a user");
        return;
    }
    
    QString username = currentItem->text();
    QString password = passwordField->text();
    
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter password");
        return;
    }
    
    qDebug() << "Emitting loginRequested signal for user:" << username;
    emit loginRequested(username, password);
    passwordField->clear();
}