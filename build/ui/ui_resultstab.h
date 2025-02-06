/********************************************************************************
** Form generated from reading UI file 'resultstab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTSTAB_H
#define UI_RESULTSTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_ResultsTab
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QLabel *lastScanLabel;
    QLabel *scanTimeLabel;
    QSpacerItem *horizontalSpacer;
    QGroupBox *metricsGroup;
    QVBoxLayout *metricsLayout;
    QCustomPlot *metricsPlot;
    QGroupBox *recommendationsGroup;
    QVBoxLayout *recommendationsLayout;
    QTextBrowser *recommendationsText;

    void setupUi(QWidget *ResultsTab)
    {
        if (ResultsTab->objectName().isEmpty())
            ResultsTab->setObjectName(QString::fromUtf8("ResultsTab"));
        ResultsTab->resize(780, 540);
        verticalLayout = new QVBoxLayout(ResultsTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName(QString::fromUtf8("headerLayout"));
        lastScanLabel = new QLabel(ResultsTab);
        lastScanLabel->setObjectName(QString::fromUtf8("lastScanLabel"));

        headerLayout->addWidget(lastScanLabel);

        scanTimeLabel = new QLabel(ResultsTab);
        scanTimeLabel->setObjectName(QString::fromUtf8("scanTimeLabel"));

        headerLayout->addWidget(scanTimeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        headerLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(headerLayout);

        metricsGroup = new QGroupBox(ResultsTab);
        metricsGroup->setObjectName(QString::fromUtf8("metricsGroup"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(7);
        sizePolicy.setHeightForWidth(metricsGroup->sizePolicy().hasHeightForWidth());
        metricsGroup->setSizePolicy(sizePolicy);
        metricsLayout = new QVBoxLayout(metricsGroup);
        metricsLayout->setObjectName(QString::fromUtf8("metricsLayout"));
        metricsPlot = new QCustomPlot(metricsGroup);
        metricsPlot->setObjectName(QString::fromUtf8("metricsPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(metricsPlot->sizePolicy().hasHeightForWidth());
        metricsPlot->setSizePolicy(sizePolicy1);
        metricsPlot->setMinimumSize(QSize(0, 300));
        metricsPlot->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);\n"
"border: 1px solid gray;"));

        metricsLayout->addWidget(metricsPlot);


        verticalLayout->addWidget(metricsGroup);

        recommendationsGroup = new QGroupBox(ResultsTab);
        recommendationsGroup->setObjectName(QString::fromUtf8("recommendationsGroup"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(recommendationsGroup->sizePolicy().hasHeightForWidth());
        recommendationsGroup->setSizePolicy(sizePolicy2);
        recommendationsLayout = new QVBoxLayout(recommendationsGroup);
        recommendationsLayout->setObjectName(QString::fromUtf8("recommendationsLayout"));
        recommendationsText = new QTextBrowser(recommendationsGroup);
        recommendationsText->setObjectName(QString::fromUtf8("recommendationsText"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(recommendationsText->sizePolicy().hasHeightForWidth());
        recommendationsText->setSizePolicy(sizePolicy3);
        recommendationsText->setMinimumSize(QSize(0, 100));

        recommendationsLayout->addWidget(recommendationsText);


        verticalLayout->addWidget(recommendationsGroup);


        retranslateUi(ResultsTab);

        QMetaObject::connectSlotsByName(ResultsTab);
    } // setupUi

    void retranslateUi(QWidget *ResultsTab)
    {
        lastScanLabel->setText(QCoreApplication::translate("ResultsTab", "Last Scan:", nullptr));
        scanTimeLabel->setText(QCoreApplication::translate("ResultsTab", "Not Available", nullptr));
        metricsGroup->setTitle(QCoreApplication::translate("ResultsTab", "Health Metrics", nullptr));
        recommendationsGroup->setTitle(QCoreApplication::translate("ResultsTab", "Potential symptoms and recommendations", nullptr));
        (void)ResultsTab;
    } // retranslateUi

};

namespace Ui {
    class ResultsTab: public Ui_ResultsTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTSTAB_H
