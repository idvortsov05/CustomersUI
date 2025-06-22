#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    void registrationComplete(const QJsonObject &customerData);

private slots:
    void handleRegistration();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
