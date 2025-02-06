/********************************************************************************
** Form generated from reading UI file 'profiletab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILETAB_H
#define UI_PROFILETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileTab
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *personalInfoGroup;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *ageLabel;
    QSpinBox *ageSpinBox;
    QLabel *genderLabel;
    QComboBox *genderComboBox;
    QLabel *heightLabel;
    QSpinBox *heightSpinBox;
    QLabel *weightLabel;
    QSpinBox *weightSpinBox;
    QGroupBox *medicalInfoGroup;
    QFormLayout *formLayout_2;
    QLabel *conditionsLabel;
    QTextEdit *conditionsEdit;
    QLabel *medicationsLabel;
    QTextEdit *medicationsEdit;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveProfileButton;

    void setupUi(QWidget *ProfileTab)
    {
        if (ProfileTab->objectName().isEmpty())
            ProfileTab->setObjectName(QString::fromUtf8("ProfileTab"));
        ProfileTab->resize(780, 500);
        verticalLayout = new QVBoxLayout(ProfileTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        personalInfoGroup = new QGroupBox(ProfileTab);
        personalInfoGroup->setObjectName(QString::fromUtf8("personalInfoGroup"));
        formLayout = new QFormLayout(personalInfoGroup);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        nameLabel = new QLabel(personalInfoGroup);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(personalInfoGroup);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        ageLabel = new QLabel(personalInfoGroup);
        ageLabel->setObjectName(QString::fromUtf8("ageLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, ageLabel);

        ageSpinBox = new QSpinBox(personalInfoGroup);
        ageSpinBox->setObjectName(QString::fromUtf8("ageSpinBox"));
        ageSpinBox->setMinimum(1);
        ageSpinBox->setMaximum(120);

        formLayout->setWidget(1, QFormLayout::FieldRole, ageSpinBox);

        genderLabel = new QLabel(personalInfoGroup);
        genderLabel->setObjectName(QString::fromUtf8("genderLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, genderLabel);

        genderComboBox = new QComboBox(personalInfoGroup);
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->addItem(QString());
        genderComboBox->setObjectName(QString::fromUtf8("genderComboBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, genderComboBox);

        heightLabel = new QLabel(personalInfoGroup);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, heightLabel);

        heightSpinBox = new QSpinBox(personalInfoGroup);
        heightSpinBox->setObjectName(QString::fromUtf8("heightSpinBox"));
        heightSpinBox->setMinimum(50);
        heightSpinBox->setMaximum(250);

        formLayout->setWidget(3, QFormLayout::FieldRole, heightSpinBox);

        weightLabel = new QLabel(personalInfoGroup);
        weightLabel->setObjectName(QString::fromUtf8("weightLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, weightLabel);

        weightSpinBox = new QSpinBox(personalInfoGroup);
        weightSpinBox->setObjectName(QString::fromUtf8("weightSpinBox"));
        weightSpinBox->setMinimum(20);
        weightSpinBox->setMaximum(200);

        formLayout->setWidget(4, QFormLayout::FieldRole, weightSpinBox);


        verticalLayout->addWidget(personalInfoGroup);

        medicalInfoGroup = new QGroupBox(ProfileTab);
        medicalInfoGroup->setObjectName(QString::fromUtf8("medicalInfoGroup"));
        formLayout_2 = new QFormLayout(medicalInfoGroup);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        conditionsLabel = new QLabel(medicalInfoGroup);
        conditionsLabel->setObjectName(QString::fromUtf8("conditionsLabel"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, conditionsLabel);

        conditionsEdit = new QTextEdit(medicalInfoGroup);
        conditionsEdit->setObjectName(QString::fromUtf8("conditionsEdit"));
        conditionsEdit->setMaximumSize(QSize(16777215, 60));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, conditionsEdit);

        medicationsLabel = new QLabel(medicalInfoGroup);
        medicationsLabel->setObjectName(QString::fromUtf8("medicationsLabel"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, medicationsLabel);

        medicationsEdit = new QTextEdit(medicalInfoGroup);
        medicationsEdit->setObjectName(QString::fromUtf8("medicationsEdit"));
        medicationsEdit->setMaximumSize(QSize(16777215, 60));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, medicationsEdit);


        verticalLayout->addWidget(medicalInfoGroup);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(horizontalSpacer);

        saveProfileButton = new QPushButton(ProfileTab);
        saveProfileButton->setObjectName(QString::fromUtf8("saveProfileButton"));

        buttonLayout->addWidget(saveProfileButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(ProfileTab);

        QMetaObject::connectSlotsByName(ProfileTab);
    } // setupUi

    void retranslateUi(QWidget *ProfileTab)
    {
        personalInfoGroup->setTitle(QCoreApplication::translate("ProfileTab", "Personal Information", nullptr));
        nameLabel->setText(QCoreApplication::translate("ProfileTab", "Full Name:", nullptr));
        ageLabel->setText(QCoreApplication::translate("ProfileTab", "Age:", nullptr));
        genderLabel->setText(QCoreApplication::translate("ProfileTab", "Gender:", nullptr));
        genderComboBox->setItemText(0, QCoreApplication::translate("ProfileTab", "Male", nullptr));
        genderComboBox->setItemText(1, QCoreApplication::translate("ProfileTab", "Female", nullptr));
        genderComboBox->setItemText(2, QCoreApplication::translate("ProfileTab", "Other", nullptr));

        heightLabel->setText(QCoreApplication::translate("ProfileTab", "Height (cm):", nullptr));
        weightLabel->setText(QCoreApplication::translate("ProfileTab", "Weight (kg):", nullptr));
        medicalInfoGroup->setTitle(QCoreApplication::translate("ProfileTab", "Medical Information", nullptr));
        conditionsLabel->setText(QCoreApplication::translate("ProfileTab", "Medical Conditions:", nullptr));
        medicationsLabel->setText(QCoreApplication::translate("ProfileTab", "Current Medications:", nullptr));
        saveProfileButton->setText(QCoreApplication::translate("ProfileTab", "Save Profile", nullptr));
        (void)ProfileTab;
    } // retranslateUi

};

namespace Ui {
    class ProfileTab: public Ui_ProfileTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILETAB_H
