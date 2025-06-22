#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QJsonObject>
#include "ui_FormCart.h"
#include "http_client/http_requests/Requests.h"

namespace Ui {
    class Form_cart;
}

class MainWindow;

class CartWindow : public QWidget
{
Q_OBJECT

public:
    explicit CartWindow(Requests* requests, QWidget *parent = nullptr);
    void loadCart();
    ~CartWindow();

private slots:
    void onOrderClicked();
    void onClearClicked();
    void onExitClicked();

private:
    void populateTable(const QJsonObject &cartData);
    void generatePdfReport(const QJsonObject &orderData);

    Ui::Form_cart *ui;
    QStandardItemModel *model;
    Requests* requests;
};

#endif // CARTWINDOW_H

