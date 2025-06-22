#ifndef HTTP_CLIENT_EDITPROFILEWINDOW_H
#define HTTP_CLIENT_EDITPROFILEWINDOW_H

#include <QWidget>
#include <QJsonObject>
#include "edit_profile_ui.h"

class EditProfileWindow : public QWidget
{
Q_OBJECT

public:
    explicit EditProfileWindow(QWidget *parent = nullptr);
    ~EditProfileWindow();

    void setProfileData(const QJsonObject &customerData);

signals:
    void profileUpdated(const QString &name,const QString &phone,const QString &contacts,const QString &address, const QString &email);

private slots:
    void applyChanges();
    void closeWindow();

private:
    Ui::Form *ui;
};

#endif // HTTP_CLIENT_EDITPROFILEWINDOW_H

