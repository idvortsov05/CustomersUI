#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "ui_Login_form.h"
#include "http_client/http_requests/Requests.h"

class RegisterDialog;

class LoginWindow : public QDialog
{
Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow() {};

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_register_clicked();
    void handleRegistrationSuccess(const QJsonObject &customerData);

private:
    Ui::login_window *ui;
    Requests *requests;
    bool authorized;
    RegisterDialog *registerDialog;
};

#endif // LOGINWINDOW_H


