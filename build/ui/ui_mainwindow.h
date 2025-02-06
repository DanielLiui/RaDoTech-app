/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *userSelectionPage;
    QWidget *mainAppPage;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *headerLayout;
    QLabel *currentUserLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *batteryLabel;
    QPushButton *logoutButton;
    QTabWidget *mainTabWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        userSelectionPage = new QWidget();
        userSelectionPage->setObjectName(QString::fromUtf8("userSelectionPage"));
        stackedWidget->addWidget(userSelectionPage);
        mainAppPage = new QWidget();
        mainAppPage->setObjectName(QString::fromUtf8("mainAppPage"));
        verticalLayout_2 = new QVBoxLayout(mainAppPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        currentUserLabel = new QLabel(mainAppPage);
        currentUserLabel->setObjectName(QString::fromUtf8("currentUserLabel"));

        headerLayout->addWidget(currentUserLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(horizontalSpacer);

        batteryLabel = new QLabel(mainAppPage);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));

        headerLayout->addWidget(batteryLabel);

        logoutButton = new QPushButton(mainAppPage);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));

        headerLayout->addWidget(logoutButton);


        verticalLayout_2->addLayout(headerLayout);

        mainTabWidget = new QTabWidget(mainAppPage);
        mainTabWidget->setObjectName(QString::fromUtf8("mainTabWidget"));

        verticalLayout_2->addWidget(mainTabWidget);

        stackedWidget->addWidget(mainAppPage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "RaDoTech Health Monitor", nullptr));
        currentUserLabel->setText(QCoreApplication::translate("MainWindow", "Current User: ", nullptr));
        batteryLabel->setText(QCoreApplication::translate("MainWindow", "Battery: 100%", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
