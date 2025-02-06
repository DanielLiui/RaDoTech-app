#include "profiletab.h"
#include "ui_profiletab.h"
#include <QMessageBox>

ProfileTab::ProfileTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileTab)
{
    ui->setupUi(this);
    setupConnections();
}

ProfileTab::~ProfileTab()
{
    delete ui;
}

void ProfileTab::setupConnections() {
    connect(ui->saveProfileButton, &QPushButton::clicked,
            this, &ProfileTab::handleSaveProfile);
}


void ProfileTab::loadUserData(const UserData& userData) {
    currentUsername = userData.username;
    ui->nameEdit->setText(userData.fullName);
    ui->ageSpinBox->setValue(userData.age);
    
    int genderIndex = ui->genderComboBox->findText(userData.gender);
    if (genderIndex >= 0) {
        ui->genderComboBox->setCurrentIndex(genderIndex);
    }
    
    ui->heightSpinBox->setValue(userData.height);
    ui->weightSpinBox->setValue(userData.weight);
    ui->conditionsEdit->setText(userData.medicalConditions);
    ui->medicationsEdit->setText(userData.medications);
}

void ProfileTab::handleSaveProfile() {
    UserData updatedData;
    updatedData.username = currentUsername;
    updatedData.fullName = ui->nameEdit->text();
    updatedData.age = ui->ageSpinBox->value();
    updatedData.gender = ui->genderComboBox->currentText();
    updatedData.height = ui->heightSpinBox->value();
    updatedData.weight = ui->weightSpinBox->value();
    updatedData.medicalConditions = ui->conditionsEdit->toPlainText();
    updatedData.medications = ui->medicationsEdit->toPlainText();

    emit profileUpdated(updatedData);
    QMessageBox::information(this, "Success", "Profile updated successfully");
}