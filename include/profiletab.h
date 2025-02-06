#ifndef PROFILETAB_H
#define PROFILETAB_H

#include <QWidget>
#include "userdata.h"

namespace Ui {
class ProfileTab;
}

class ProfileTab : public QWidget {
    Q_OBJECT

public:
    explicit ProfileTab(QWidget *parent = nullptr);
    ~ProfileTab();
    void loadUserData(const UserData& userData);

signals:
    void profileUpdated(const UserData& userData);

private slots:
    void handleSaveProfile();

private:
    Ui::ProfileTab *ui;
    QString currentUsername;
    void setupConnections();
};

#endif // PROFILETAB_H