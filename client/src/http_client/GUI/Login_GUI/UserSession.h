#ifndef HTTP_CLIENT_USERSESSION_H
#define HTTP_CLIENT_USERSESSION_H

#include <QObject>

class UserSession
{
public:
    static UserSession& instance()
    {
        static UserSession instance;
        return instance;
    }

    void updateCustomerData(const QString& name, const QString& phone, const QString& email, const QString& address, const QString& contactPerson)
    {
        customerName = name;
        customerPhone = phone;
        customerEmail = email;
        customerAddress = address;
        customerContactPerson = contactPerson;
    }

    void setCustomerData(int id, const QString& name, const QString& email,
                         const QString& phone, const QString& address,
                         const QString& contactPerson) {
        customerId = id;
        customerName = name;
        customerEmail = email;
        customerPhone = phone;
        customerAddress = address;
        customerContactPerson = contactPerson;
    }

    int getCustomerId() const { return customerId; }
    QString getCustomerName() const { return customerName; }
    QString getCustomerEmail() const { return customerEmail; }
    QString getCustomerPhone() const { return customerPhone; }
    QString getCustomerAddress() const { return customerAddress; }
    QString getCustomerContactPerson() const { return customerContactPerson; }
    bool isLoggedIn() const { return customerId != -1; }

private:
    UserSession() : customerId(-1) {}

    int customerId;
    QString customerName;
    QString customerEmail;
    QString customerPhone;
    QString customerAddress;
    QString customerContactPerson;
};

#endif //HTTP_CLIENT_USERSESSION_H
