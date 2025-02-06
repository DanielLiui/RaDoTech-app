/********************************************************************************
** Form generated from reading UI file 'historytab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYTAB_H
#define UI_HISTORYTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoryTab
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *filterLayout;
    QLabel *dateRangeLabel;
    QDateEdit *startDateEdit;
    QLabel *toLabel;
    QDateEdit *endDateEdit;
    QPushButton *applyFilterButton;
    QSpacerItem *horizontalSpacer;
    QTableWidget *historyTable;

    void setupUi(QWidget *HistoryTab)
    {
        if (HistoryTab->objectName().isEmpty())
            HistoryTab->setObjectName(QString::fromUtf8("HistoryTab"));
        HistoryTab->resize(780, 500);
        verticalLayout = new QVBoxLayout(HistoryTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        filterLayout = new QHBoxLayout();
        filterLayout->setObjectName(QString::fromUtf8("filterLayout"));
        dateRangeLabel = new QLabel(HistoryTab);
        dateRangeLabel->setObjectName(QString::fromUtf8("dateRangeLabel"));

        filterLayout->addWidget(dateRangeLabel);

        startDateEdit = new QDateEdit(HistoryTab);
        startDateEdit->setObjectName(QString::fromUtf8("startDateEdit"));
        startDateEdit->setCalendarPopup(true);

        filterLayout->addWidget(startDateEdit);

        toLabel = new QLabel(HistoryTab);
        toLabel->setObjectName(QString::fromUtf8("toLabel"));

        filterLayout->addWidget(toLabel);

        endDateEdit = new QDateEdit(HistoryTab);
        endDateEdit->setObjectName(QString::fromUtf8("endDateEdit"));
        endDateEdit->setCalendarPopup(true);

        filterLayout->addWidget(endDateEdit);

        applyFilterButton = new QPushButton(HistoryTab);
        applyFilterButton->setObjectName(QString::fromUtf8("applyFilterButton"));

        filterLayout->addWidget(applyFilterButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        filterLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(filterLayout);

        historyTable = new QTableWidget(HistoryTab);
        if (historyTable->columnCount() < 7)
            historyTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        historyTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        historyTable->setObjectName(QString::fromUtf8("historyTable"));

        verticalLayout->addWidget(historyTable);


        retranslateUi(HistoryTab);

        QMetaObject::connectSlotsByName(HistoryTab);
    } // setupUi

    void retranslateUi(QWidget *HistoryTab)
    {
        dateRangeLabel->setText(QCoreApplication::translate("HistoryTab", "Date Range:", nullptr));
        startDateEdit->setDisplayFormat(QCoreApplication::translate("HistoryTab", "yyyy-MM-dd", nullptr));
        toLabel->setText(QCoreApplication::translate("HistoryTab", "to", nullptr));
        endDateEdit->setDisplayFormat(QCoreApplication::translate("HistoryTab", "yyyy-MM-dd", nullptr));
        applyFilterButton->setText(QCoreApplication::translate("HistoryTab", "Apply Filter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = historyTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("HistoryTab", "Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = historyTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("HistoryTab", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = historyTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("HistoryTab", "Score", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = historyTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("HistoryTab", "Left Hand (H1-H6)", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = historyTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("HistoryTab", "Right Hand (H1-H6)", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = historyTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("HistoryTab", "Left Foot (F1-F6)", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = historyTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("HistoryTab", "Right Foot (F1-F6)", nullptr));
        (void)HistoryTab;
    } // retranslateUi

};

namespace Ui {
    class HistoryTab: public Ui_HistoryTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYTAB_H
