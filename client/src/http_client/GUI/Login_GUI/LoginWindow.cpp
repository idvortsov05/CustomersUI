#include "LoginWindow.h"
#include "RegisterDialog.h"
#include "UserSession.h"
#include <QMessageBox>
#include <QCryptographicHash>

LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent), ui(new Ui::login_window), requests(new Requests(this)), authorized(false), registerDialog(nullptr)
{
    ui->setupUi(this);

    connect(ui->pushButton_login, &QPushButton::clicked,this, &LoginWindow::on_pushButton_login_clicked);
    connect(ui->pushButton_register, &QPushButton::clicked,this, &LoginWindow::on_pushButton_register_clicked);
}

void LoginWindow::on_pushButton_login_clicked()
{
    QString email = ui->textEdit_login->toPlainText().trimmed();
    QString password = ui->textEdit_password->toPlainText().trimmed();

    if(email.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Заполните все поля");
        return;
    }

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha256).toHex().toLower();

    QJsonObject credentials;
    credentials["email"] = email;
    credentials["password"] = QString(hashedPassword);

    QJsonObject response = requests->login(credentials);
    qDebug() << "Login response:" << response;

    if(response.contains("CustomerID"))
    {
        UserSession::instance().setCustomerData(
                response["CustomerID"].toInt(),
                response["Name"].toString(),
                response["Email"].toString(),
                response["Phone"].toString(),
                response["Address"].toString(),
                response["ContactPerson"].toString()
        );

        this->done(QDialog::Accepted);
    }
    else
    {
        QString error = response.value("detail").toString("Ошибка авторизации");
        QMessageBox::warning(this, "Ошибка", error);
    }
}

void LoginWindow::on_pushButton_register_clicked()
{
    if(!registerDialog)
    {
        registerDialog = new RegisterDialog(this);
        connect(registerDialog, &RegisterDialog::registrationComplete,this, &LoginWindow::handleRegistrationSuccess);
    }
    registerDialog->show();
}

void LoginWindow::handleRegistrationSuccess(const QJsonObject &customerData)
{
    if(customerData.contains("CustomerID"))
    {
        authorized = true;
        UserSession::instance().setCustomerData(
                customerData["CustomerID"].toInt(),
                customerData["Name"].toString(),
                customerData["Email"].toString(),
                customerData["Phone"].toString(),
                customerData["Address"].toString(),
                customerData["ContactPerson"].toString()
        );
        this->accept();
    }
}







