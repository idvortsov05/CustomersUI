#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "http_client/http_requests/Requests.h"
#include <QCryptographicHash>
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent) : QDialog(parent), ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    setWindowTitle("Регистрация нового пользователя");

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_phone->setInputMask("+7(999)999-99-99");
    ui->lineEdit_password->setPlaceholderText("Минимум 8 символов");

    connect(ui->pushButton, &QPushButton::clicked,this, &RegisterDialog::handleRegistration);
}

void RegisterDialog::handleRegistration()
{
    QString name = ui->lineEdit_name->text().trimmed();
    QString email = ui->lineEdit_email->text().trimmed();
    QString phone = ui->lineEdit_phone->text().trimmed();
    QString address = ui->lineEdit_address->text().trimmed();
    QString contactPerson = ui->lineEdit_contact->text().trimmed();
    QString password = ui->lineEdit_password->text();

    if(name.isEmpty() || email.isEmpty() || phone.isEmpty() || address.isEmpty() || contactPerson.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Заполните все обязательные поля");
        return;
    }

    phone = phone.replace("(", "").replace(")", "").replace("-", "");

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha256).toHex().toLower();

    QJsonObject customerData;
    customerData["name"] = name;
    customerData["email"] = email;
    customerData["phone"] = phone;
    customerData["address"] = address;
    customerData["contact_person"] = contactPerson;
    customerData["password"] = QString(hashedPassword);

    Requests requests(this);
    QJsonObject response = requests.registerCustomer(customerData);

    if(response.contains("CustomerID"))
    {
        QMessageBox::information(this, "Успех", "Регистрация прошла успешно!");
        emit registrationComplete(response);
        this->close();
    }
    else
    {
        QString error = response.value("detail").toString("Ошибка регистрации");
        QMessageBox::warning(this, "Ошибка", error);
    }
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}