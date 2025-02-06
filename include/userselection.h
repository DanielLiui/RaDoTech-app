#ifndef USERSELECTION_H
#define USERSELECTION_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
class UserSelection;
}

class UserSelection : public QWidget {
    Q_OBJECT

public:
    explicit UserSelection(QWidget *parent = nullptr);
    ~UserSelection();
    void updateUserList(const QStringList& usernames);

signals:
    void loginRequested(const QString& username, const QString& password);
    void newUserAdded(const QString& username, const QString& password);
    void userDeleted(const QString& username);

private slots:
    void handleAddUser();
    void handleDeleteUser();
    void handleSelectUser();

private:
    Ui::UserSelection *ui;
    QLineEdit* passwordField;
    void setupUI();
};

#endif