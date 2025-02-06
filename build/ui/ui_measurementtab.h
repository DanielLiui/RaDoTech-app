/********************************************************************************
** Form generated from reading UI file 'measurementtab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASUREMENTTAB_H
#define UI_MEASUREMENTTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeasurementTab
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *instructionLabel;
    QLabel *placeholderLabel;
    QProgressBar *measurementProgress;
    QHBoxLayout *buttonLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *actionButton;
    QPushButton *startScanButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *MeasurementTab)
    {
        if (MeasurementTab->objectName().isEmpty())
            MeasurementTab->setObjectName(QString::fromUtf8("MeasurementTab"));
        MeasurementTab->resize(780, 500);
        verticalLayout = new QVBoxLayout(MeasurementTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        instructionLabel = new QLabel(MeasurementTab);
        instructionLabel->setObjectName(QString::fromUtf8("instructionLabel"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        instructionLabel->setFont(font);
        instructionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(instructionLabel);

        placeholderLabel = new QLabel(MeasurementTab);
        placeholderLabel->setObjectName(QString::fromUtf8("placeholderLabel"));
        placeholderLabel->setMinimumSize(QSize(0, 300));
        placeholderLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);\n"
"border: 1px solid gray;"));
        placeholderLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(placeholderLabel);

        measurementProgress = new QProgressBar(MeasurementTab);
        measurementProgress->setObjectName(QString::fromUtf8("measurementProgress"));
        measurementProgress->setValue(0);

        verticalLayout->addWidget(measurementProgress);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(horizontalSpacer);

        actionButton = new QPushButton(MeasurementTab);
        actionButton->setObjectName(QString::fromUtf8("actionButton"));
        actionButton->setMinimumSize(QSize(120, 0));

        buttonLayout->addWidget(actionButton);

        startScanButton = new QPushButton(MeasurementTab);
        startScanButton->setObjectName(QString::fromUtf8("startScanButton"));
        startScanButton->setMinimumSize(QSize(120, 0));

        buttonLayout->addWidget(startScanButton);

        cancelButton = new QPushButton(MeasurementTab);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setMinimumSize(QSize(120, 0));

        buttonLayout->addWidget(cancelButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(MeasurementTab);

        QMetaObject::connectSlotsByName(MeasurementTab);
    } // setupUi

    void retranslateUi(QWidget *MeasurementTab)
    {
        instructionLabel->setText(QCoreApplication::translate("MeasurementTab", "Measurement Instructions", nullptr));
        measurementProgress->setFormat(QCoreApplication::translate("MeasurementTab", "Progress: %p%", nullptr));
        actionButton->setText(QCoreApplication::translate("MeasurementTab", "Place Probe", nullptr));
        startScanButton->setText(QCoreApplication::translate("MeasurementTab", "Start Scan", nullptr));
        cancelButton->setText(QCoreApplication::translate("MeasurementTab", "Cancel", nullptr));
        (void)MeasurementTab;
    } // retranslateUi

};

namespace Ui {
    class MeasurementTab: public Ui_MeasurementTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREMENTTAB_H
