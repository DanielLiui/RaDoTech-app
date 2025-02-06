/********************************************************************************
** Form generated from reading UI file 'userselection.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSELECTION_H
#define UI_USERSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserSelection
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *titleLabel;
    QLabel *batteryLabel;
    QLabel *selectUserLabel;
    QListWidget *userListWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *addUserButton;
    QPushButton *deleteUserButton;
    QPushButton *selectUserButton;

    void setupUi(QWidget *UserSelection)
    {
        if (UserSelection->objectName().isEmpty())
            UserSelection->setObjectName(QString::fromUtf8("UserSelection"));
        UserSelection->resize(800, 600);
        verticalLayout = new QVBoxLayout(UserSelection);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        titleLabel = new QLabel(UserSelection);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        headerLayout->addWidget(titleLabel);

        batteryLabel = new QLabel(UserSelection);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));

        headerLayout->addWidget(batteryLabel);


        verticalLayout->addLayout(headerLayout);

        selectUserLabel = new QLabel(UserSelection);
        selectUserLabel->setObjectName(QString::fromUtf8("selectUserLabel"));

        verticalLayout->addWidget(selectUserLabel);

        userListWidget = new QListWidget(UserSelection);
        userListWidget->setObjectName(QString::fromUtf8("userListWidget"));
        userListWidget->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(userListWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        addUserButton = new QPushButton(UserSelection);
        addUserButton->setObjectName(QString::fromUtf8("addUserButton"));

        buttonLayout->addWidget(addUserButton);

        deleteUserButton = new QPushButton(UserSelection);
        deleteUserButton->setObjectName(QString::fromUtf8("deleteUserButton"));

        buttonLayout->addWidget(deleteUserButton);

        selectUserButton = new QPushButton(UserSelection);
        selectUserButton->setObjectName(QString::fromUtf8("selectUserButton"));

        buttonLayout->addWidget(selectUserButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(UserSelection);

        QMetaObject::connectSlotsByName(UserSelection);
    } // setupUi

    void retranslateUi(QWidget *UserSelection)
    {
        UserSelection->setWindowTitle(QCoreApplication::translate("UserSelection", "User Selection", nullptr));
        titleLabel->setText(QCoreApplication::translate("UserSelection", "RaDoTech Health Monitor", nullptr));
        batteryLabel->setText(QCoreApplication::translate("UserSelection", "Battery: 100%", nullptr));
        selectUserLabel->setText(QCoreApplication::translate("UserSelection", "Select User Profile:", nullptr));
        addUserButton->setText(QCoreApplication::translate("UserSelection", "Add New User", nullptr));
        deleteUserButton->setText(QCoreApplication::translate("UserSelection", "Delete User", nullptr));
        selectUserButton->setText(QCoreApplication::translate("UserSelection", "Select User", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserSelection: public Ui_UserSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSELECTION_H
