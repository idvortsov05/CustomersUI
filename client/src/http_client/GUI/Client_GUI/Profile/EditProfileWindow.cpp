#include <QMessageBox>
#include "EditProfileWindow.h"

EditProfileWindow::EditProfileWindow(QWidget *parent) : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);

    connect(ui->pushButton_apply_changes, &QPushButton::clicked, this, &EditProfileWindow::applyChanges);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, &EditProfileWindow::closeWindow);

}

EditProfileWindow::~EditProfileWindow()
{
    delete ui;
}

void EditProfileWindow::setProfileData(const QJsonObject &customerData)
{
    ui->textEdit_name->setText(customerData["Name"].toString());
    ui->textEdit_phone->setText(customerData["Phone"].toString());
    ui->textEdit_email->setText(customerData["Email"].toString());
    ui->textEdit_contacts->setText(customerData["ContactPerson"].toString());
    ui->textEdit_address->setText(customerData["Address"].toString());
}

void EditProfileWindow::applyChanges()
{
    QJsonObject updatedData;
    updatedData["Name"] = ui->textEdit_name->toPlainText().trimmed();
    updatedData["Phone"] = ui->textEdit_phone->toPlainText().replace("(", "").replace(")", "").replace("-", "").trimmed();
    updatedData["Email"] = ui->textEdit_email->toPlainText().trimmed();
    updatedData["ContactPerson"] = ui->textEdit_contacts->toPlainText().trimmed();
    updatedData["Address"] = ui->textEdit_address->toPlainText().trimmed();

    if (updatedData["Name"].toString().isEmpty() ||
        updatedData["Phone"].toString().isEmpty() ||
        updatedData["Email"].toString().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя, телефон и email обязательны для заполнения");
        return;
    }

    emit profileUpdated(
            updatedData["Name"].toString(),
            updatedData["Phone"].toString(),
            updatedData["ContactPerson"].toString(),
            updatedData["Address"].toString(),
            updatedData["Email"].toString()
    );

    close();
}

void EditProfileWindow::closeWindow()
{
    this->close();
}


