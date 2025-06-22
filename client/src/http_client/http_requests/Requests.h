#ifndef REQUESTS_H
#define REQUESTS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <limits>
#include <QUrlQuery>


class Requests : public QObject
{
    Q_OBJECT

public:
     explicit Requests(QObject* parent = nullptr);

    // Товары
    QJsonArray getAllProducts();
    QJsonArray getSortedProducts(const QString &field, const QString &order);
    QJsonArray searchProducts(const QString &query);

    // Профиль
    QJsonObject getCustomerInfo(int customerId);
    bool updateCustomerInfo(int customerId, const QJsonObject &data);

    // Корзина
    QJsonObject getCart(int customerId);
    QJsonObject clearCart(int customerId);
    QJsonObject addToCart(int customerId, int productId, int quantity);
    bool removeFromCart(int customerId, int productId);
    bool checkout(int customerId);

    // Заказы
    QJsonArray getOrders(int customerId);
    QJsonObject placeOrder(int customerId, const QJsonObject &orderData);

    // Авторизация
    QJsonObject login(const QJsonObject &credentials);
    QJsonObject registerCustomer(const QJsonObject &customerData);


private:
    QNetworkAccessManager* manager;

    QNetworkReply* sendRequest(const QString &url, const QUrlQuery &params = QUrlQuery(), const QByteArray &verb = "GET", const QByteArray &data = QByteArray());
};

#endif // REQUESTS_H



