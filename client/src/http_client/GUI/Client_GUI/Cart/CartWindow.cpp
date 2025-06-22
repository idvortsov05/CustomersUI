#include "CartWindow.h"
#include "http_client/GUI/Login_GUI/UserSession.h"
#include "http_client/GUI/Client_GUI/MainWindow.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>

#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFileDialog>

CartWindow::CartWindow(Requests* requests, QWidget *parent) : QWidget(parent), ui(new Ui::Form_cart), model(new QStandardItemModel(this)), requests(requests)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent);

    if (mainWindow)
        connect(mainWindow, &MainWindow::cartUpdated, this, &CartWindow::loadCart);

    connect(ui->pushButton_order, &QPushButton::clicked, this, &CartWindow::onOrderClicked);
    connect(ui->pushButton_order_2, &QPushButton::clicked, this, &CartWindow::onClearClicked);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, &CartWindow::onExitClicked);

    loadCart();
}

void CartWindow::loadCart()
{
    int customerId = UserSession::instance().getCustomerId();
    if (customerId <= 0)
    {
        QMessageBox::warning(this, "Ошибка", "Пользователь не авторизован");
        return;
    }

    QJsonObject cartData = requests->getCart(customerId);
    if (cartData.isEmpty())
    {
        QMessageBox::information(this, "Корзина", "Не удалось загрузить корзину");
        return;
    }

    if (cartData["items"].toArray().isEmpty())
    {
        QMessageBox::information(this, "Корзина", "Корзина пуста");
        model->clear();
        return;
    }

    populateTable(cartData);
}


void CartWindow::populateTable(const QJsonObject &cartData)
{
    model->clear();
    model->setHorizontalHeaderLabels({"Товар", "Кол-во", "Цена", "Сумма"});

    QJsonArray items = cartData["items"].toArray();
    double totalPrice = cartData["total_price"].toDouble();
    double discountedPrice = cartData["discounted_price"].toDouble();
    double discountRate = cartData["discount_rate"].toDouble() * 100;

    for (const QJsonValue &val : items)
    {
        QJsonObject obj = val.toObject();
        double price = obj["Price"].toDouble();
        int quantity = obj["Quantity"].toInt();
        double sum = price * quantity;

        QList<QStandardItem*> row;
        row << new QStandardItem(obj["ProductName"].toString());
        row << new QStandardItem(QString::number(quantity));
        row << new QStandardItem(QString::number(price, 'f', 2));
        row << new QStandardItem(QString::number(sum, 'f', 2));
        model->appendRow(row);
    }

    QList<QStandardItem*> totalRow;
    totalRow << new QStandardItem("Итого:");
    totalRow << new QStandardItem("");
    totalRow << new QStandardItem("");
    totalRow << new QStandardItem(QString::number(totalPrice, 'f', 2));

    QList<QStandardItem*> discountRow;
    discountRow << new QStandardItem(QString("Скидка (%1%)").arg(discountRate, 0, 'f', 1));
    discountRow << new QStandardItem("");
    discountRow << new QStandardItem("");
    discountRow << new QStandardItem(QString("-%1").arg(totalPrice - discountedPrice, 0, 'f', 2));

    QList<QStandardItem*> finalRow;
    finalRow << new QStandardItem("К оплате:");
    finalRow << new QStandardItem("");
    finalRow << new QStandardItem("");
    finalRow << new QStandardItem(QString::number(discountedPrice, 'f', 2));

    QFont boldFont;
    boldFont.setBold(true);
    for (auto item : totalRow + discountRow + finalRow)
    {
        item->setFont(boldFont);
        if (item->text().startsWith("К оплате:"))
        {
            item->setForeground(QBrush(Qt::blue));
        }
    }

    model->appendRow(totalRow);
    model->appendRow(discountRow);
    model->appendRow(finalRow);
    ui->tableView->resizeColumnsToContents();
}

void CartWindow::onOrderClicked()
{
    int customerId = UserSession::instance().getCustomerId();
    if (customerId <= 0)
    {
        QMessageBox::warning(this, "Ошибка", "Пользователь не авторизован");
        return;
    }

    QJsonObject orderData;
    orderData["employee_id"] = 1;
    orderData["is_wholesale"] = false;

    QJsonObject response = requests->placeOrder(customerId, orderData);

    if (response.isEmpty() || !response.contains("TransactionID") || !response.contains("details"))
    {
        QMessageBox::warning(this, "Ошибка", "Некорректный ответ от сервера.");
        return;
    }

    generatePdfReport(response);

    QMessageBox::information(this, "Успешно",
                             QString("Заказ #%1 успешно оформлен!").arg(response["TransactionID"].toInt()));

    loadCart();
}


void CartWindow::generatePdfReport(const QJsonObject &orderData)
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить отчёт", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) return;
    printer.setOutputFileName(fileName);
    QPainter painter;
    if (!painter.begin(&printer))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать PDF");
        return;
    }
    QFont headerFont;
    headerFont.setPointSize(16);
    headerFont.setBold(true);
    QFont normalFont;
    normalFont.setPointSize(14);
    const int leftMargin = 150;
    painter.setFont(headerFont);
    painter.drawText(leftMargin, 100, "ОТЧЁТ О ЗАКАЗЕ");
    painter.setFont(normalFont);
    painter.drawText(leftMargin, 300, QString("Номер заказа: #%1").arg(orderData["TransactionID"].toInt()));
    painter.drawText(leftMargin, 600, QString("Дата: %1").arg(orderData["TransactionDate"].toString()));
    painter.drawText(leftMargin, 900, QString("Тип: %1").arg(orderData["IsWholesale"].toBool() ? "Оптовый" : "Розничный"));
    painter.drawText(leftMargin, 1200, QString("Сумма: %1 ₽").arg(orderData["total_amount"].toDouble(), 0, 'f', 2));
    painter.drawText(leftMargin, 1500, QString("Скидка: %1 ₽").arg(orderData["discount_amount"].toDouble(), 0, 'f', 2));
    painter.drawText(leftMargin, 1800, QString("Итого к оплате: %1 ₽").arg( orderData["total_amount"].toDouble() - orderData["discount_amount"].toDouble(), 0, 'f', 2));
    painter.end();
    QMessageBox::information(this, "Готово", "PDF отчёт успешно создан");
}

void CartWindow::onClearClicked()
{
    int customerId = UserSession::instance().getCustomerId();
    if (customerId <= 0)
    {
        QMessageBox::warning(this, "Ошибка", "Пользователь не авторизован");
        return;
    }

    QJsonObject response = requests->clearCart(customerId);
    if (response.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось очистить корзину");
        return;
    }

    if (response.contains("message"))
    {
        QMessageBox::information(this, "Успешно", "Корзина очищена!");
        loadCart();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка",
                             response.contains("error") ? response["error"].toString() : "Неизвестная ошибка");
    }
}

void CartWindow::onExitClicked()
{
    this->close();
}

CartWindow::~CartWindow()
{
    delete model;
}