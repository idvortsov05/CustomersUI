#include <QEventLoop>
#include <QJsonDocument>
#include "Requests.h"

Requests::Requests(QObject* parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

QNetworkReply* Requests::sendRequest(const QString &url, const QUrlQuery &params, const QByteArray &verb, const QByteArray &data)
{
    QUrl fullUrl(url);
    fullUrl.setQuery(params);

    QNetworkRequest request(fullUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    QNetworkReply *reply = nullptr;
    if (verb == "GET")
    {
        reply = manager->get(request);
    }
    else if (verb == "POST")
    {
        reply = manager->post(request, data);
    }
    else if (verb == "PUT")
    {
        reply = manager->put(request, data);
    }
    else if (verb == "DELETE")
    {
        reply = manager->deleteResource(request);
    }
    else
    {
        qDebug() << "Unsupported HTTP verb:" << verb;
        return nullptr;
    }

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "HTTP Error:" << reply->errorString();
        reply->setProperty("success", false);
        return reply;
    }

    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (status >= 400)
    {
        qDebug() << "HTTP Status Error:" << status;
        reply->setProperty("success", false);
        return reply;
    }

    QByteArray responseData = reply->readAll();
    if (!responseData.isEmpty())
    {
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(responseData, &parseError);

        if (parseError.error != QJsonParseError::NoError)
        {
            qDebug() << "JSON Parse Error:" << parseError.errorString();
            reply->setProperty("success", false);
            return reply;
        }

        if (doc.isArray())
        {
            reply->setProperty("json", doc.array());
        }
        else
        {
            reply->setProperty("json", doc.object());
        }
    }

    reply->setProperty("success", true);
    return reply;
}

QJsonArray Requests::getAllProducts()
{
    QNetworkReply* reply = sendRequest("http://127.0.0.1:8080/products");

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Failed to get products";
        reply->deleteLater();
        return QJsonArray();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();

    if (response.contains("products") && response["products"].isArray())
    {
        return response["products"].toArray();
    }

    return QJsonArray();
}

QJsonArray Requests::getSortedProducts(const QString &field, const QString &order)
{
    QUrlQuery params;
    params.addQueryItem("sort_by", field + "_" + order.toLower());

    QNetworkReply* reply = sendRequest("http://127.0.0.1:8080/products", params);

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Failed to get sorted products";
        reply->deleteLater();
        return QJsonArray();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();

    if (response.contains("products") && response["products"].isArray())
    {
        return response["products"].toArray();
    }

    return QJsonArray();
}

QJsonArray Requests::searchProducts(const QString &query)
{
    QUrlQuery params;
    params.addQueryItem("query", query);

    QNetworkReply* reply = sendRequest("http://127.0.0.1:8080/products/search", params);

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Failed to search products";
        reply->deleteLater();
        return QJsonArray();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();

    if (response.contains("products") && response["products"].isArray())
    {
        return response["products"].toArray();
    }

    return QJsonArray();
}

QJsonObject Requests::getCustomerInfo(int customerId)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1").arg(customerId),
            QUrlQuery(),
            "GET"
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Failed to get customer info";
        reply->deleteLater();
        return QJsonObject();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}

bool Requests::updateCustomerInfo(int customerId, const QJsonObject &data)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1").arg(customerId),
            QUrlQuery(),
            "PUT",
            QJsonDocument(data).toJson()
    );

    if (!reply)
    {
        qDebug() << "Error: Request failed";
        return false;
    }

    bool success = reply->property("success").toBool();
    reply->deleteLater();
    return success;
}



QJsonObject Requests::getCart(int customerId)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/cart").arg(customerId),
            QUrlQuery(),
            "GET"
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Failed to get cart";
        reply->deleteLater();
        return QJsonObject();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}

QJsonObject Requests::addToCart(int customerId, int productId, int quantity)
{
    QJsonObject payload;
    payload["ProductID"] = productId;
    payload["Quantity"] = quantity;

    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/cart/items").arg(customerId),
            QUrlQuery(),
            "POST",
            QJsonDocument(payload).toJson()
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Add to cart request failed";
        reply->deleteLater();
        return QJsonObject();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}

bool Requests::removeFromCart(int customerId, int productId)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/cart/%2").arg(customerId).arg(productId),
            QUrlQuery(),
            "DELETE"
    );

    if (!reply)
    {
        qDebug() << "Error: Request failed";
        return false;
    }

    bool success = reply->property("success").toBool();
    reply->deleteLater();
    return success;
}

bool Requests::checkout(int customerId)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/checkout").arg(customerId),
            QUrlQuery(),
            "POST"
    );

    if (!reply)
    {
        qDebug() << "Error: Request failed";
        return false;
    }

    bool success = reply->property("success").toBool();
    reply->deleteLater();
    return success;
}

QJsonArray Requests::getOrders(int customerId)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/orders").arg(customerId),
            QUrlQuery(),
            "GET"
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Failed to get orders";
        reply->deleteLater();
        return QJsonArray();
    }

    QJsonArray response = reply->property("json").toJsonArray();
    reply->deleteLater();
    return response;
}

QJsonObject Requests::login(const QJsonObject &credentials)
{
    QNetworkReply* reply = sendRequest(
            "http://127.0.0.1:8080/login",
            QUrlQuery(),
            "POST",
            QJsonDocument(credentials).toJson()
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Login error:" << reply->errorString();
        qDebug() << "Response:" << reply->readAll();
        reply->deleteLater();
        return QJsonObject{{"error", "Login failed"}};
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}

QJsonObject Requests::registerCustomer(const QJsonObject &customerData)
{
    QNetworkReply* reply = sendRequest(
            "http://127.0.0.1:8080/register",
            QUrlQuery(),
            "POST",
            QJsonDocument(customerData).toJson()
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Registration failed";
        reply->deleteLater();
        return QJsonObject();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}

QJsonObject Requests::placeOrder(int customerId, const QJsonObject &orderData)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/orders").arg(customerId),
            QUrlQuery(),
            "POST",
            QJsonDocument(orderData).toJson()
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Order request failed";
        reply->deleteLater();
        return QJsonObject();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}

QJsonObject Requests::clearCart(int customerId)
{
    QNetworkReply* reply = sendRequest(
            QString("http://127.0.0.1:8080/customers/%1/cart").arg(customerId),
            QUrlQuery(),
            "DELETE"
    );

    if (!reply || !reply->property("success").toBool())
    {
        qDebug() << "Error: Clear cart request failed";
        reply->deleteLater();
        return QJsonObject();
    }

    QJsonObject response = reply->property("json").toJsonObject();
    reply->deleteLater();
    return response;
}







