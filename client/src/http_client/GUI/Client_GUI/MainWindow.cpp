#include "MainWindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QInputDialog>

#include "http_client/GUI/Login_GUI/UserSession.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          ui(new Ui::MainWindowCustomer),
          requests(new Requests(this)),
          editProfileWindow(nullptr)
{
    ui->setupUi(this);
    setupConnections();
    updateTable();

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->comboBox->addItem("По номеру", "id");
    ui->comboBox->addItem("По названию", "name");
    ui->comboBox->addItem("По оптовой цене", "wholesale_price");
    ui->comboBox->addItem("По розничной цене", "retail_price");
    ui->comboBox->addItem("По описанию", "description");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete editProfileWindow;
}

void MainWindow::setupConnections()
{
    connect(ui->pushButton_Change_info_user, &QPushButton::clicked, this, &MainWindow::edit_profile);
    connect(ui->pushButton_cart, &QPushButton::clicked, this, &MainWindow::open_cart_customer);
    connect(ui->pushButton_orders, &QPushButton::clicked, this, &MainWindow::open_orders_customer);
    connect(ui->pushButton_find_products, &QPushButton::clicked, this, &MainWindow::FindProducts);
    connect(ui->pushButton_reset_filters, &QPushButton::clicked, this, &MainWindow::ResetFilters);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, &MainWindow::Exit);
    connect(ui->pushButton_sort_products, &QPushButton::clicked, this, &MainWindow::SortProducts);
    connect(ui->pushButton_add_to_cart, &QPushButton::clicked, this, &MainWindow::onAddToCartClicked);
}

void MainWindow::initializingTable(const QJsonArray &data)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QStringList headers = {"ID", "Фото", "Название", "Оптовая цена", "Розничная цена", "Описание"};
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(data.size());

    const int imageSize = 250;
    int row = 0;

    for (const QJsonValue &value : data) {
        QJsonObject item = value.toObject();

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(item["ProductID"].toInt())));

        if (item.contains("Image") && !item["Image"].isNull()) {
            QTableWidgetItem *photoItem = createPhotoTableItem(item["Image"].toString(), imageSize);
            ui->tableWidget->setItem(row, 1, photoItem);
        }

        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(item["Name"].toString()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(item["WholesalePrice"].toDouble(), 'f', 2) + " ₽"));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(item["RetailPrice"].toDouble(), 'f', 2) + " ₽"));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(item["Description"].toString()));

        row++;
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(1, imageSize);
    ui->tableWidget->resizeRowsToContents();

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::SortProducts()
{
    QString selectedField = ui->comboBox->currentData().toString();

    if (selectedField.isEmpty()) {
        qDebug() << "Не выбрано поле для сортировки!";
        return;
    }

    static QString lastField;
    static bool isAscending = true;

    if (selectedField == lastField) {
        isAscending = !isAscending;
    } else {
        isAscending = true;
        lastField = selectedField;
    }

    QJsonArray sortedResults = requests->getSortedProducts(selectedField, isAscending ? "asc" : "desc");

    if (sortedResults.isEmpty()) {
        QMessageBox::information(this, "Сортировка", "Нет данных для отображения");
        return;
    }

    initializingTable(sortedResults);
}

QTableWidgetItem* MainWindow::createPhotoTableItem(const QString &base64String, int size)
{
    QByteArray imageData = QByteArray::fromBase64(base64String.toUtf8());
    QPixmap pixmap;
    pixmap.loadFromData(imageData);

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DecorationRole, pixmap.scaled(size, size, Qt::KeepAspectRatio));
    return item;
}

void MainWindow::updateTable()
{
    QJsonArray products = requests->getAllProducts();
    if (products.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить товары");
        return;
    }
    initializingTable(products);
}

void MainWindow::FindProducts()
{
    QString searchText = ui->textEdit_find_product->toPlainText().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::information(this, "Поиск", "Введите критерии поиска");
        return;
    }

    QJsonArray results = requests->searchProducts(searchText);
    if (results.isEmpty()) {
        QMessageBox::information(this, "Поиск", "Товары не найдены");
        return;
    }

    initializingTable(results);
}

void MainWindow::ResetFilters()
{
    ui->textEdit_find_product->clear();
    ui->comboBox->setCurrentIndex(0);
    updateTable();
}

void MainWindow::edit_profile()
{
    const auto& session = UserSession::instance();

    if (session.getCustomerId() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Пользователь не авторизован");
        return;
    }

    if (!editProfileWindow) {
        editProfileWindow = new EditProfileWindow(nullptr);
        connect(editProfileWindow, &EditProfileWindow::profileUpdated,
                this, &MainWindow::handleProfileUpdate);
    }

    QJsonObject customerData = requests->getCustomerInfo(session.getCustomerId());
    if (customerData.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные профиля");
        return;
    }

    editProfileWindow->setProfileData(customerData);
    editProfileWindow->show();
    editProfileWindow->raise();
    editProfileWindow->activateWindow();
}


void MainWindow::handleProfileUpdate(const QString &name,
                                     const QString &phone,
                                     const QString &contacts,
                                     const QString &address,
                                     const QString &email)
{
    QJsonObject updatedData;
    updatedData["Name"] = name;
    updatedData["Phone"] = phone;
    updatedData["ContactPerson"] = contacts;
    updatedData["Address"] = address;
    updatedData["Email"] = email;

    qDebug() << "Sending updated data:" << updatedData;

    bool success = requests->updateCustomerInfo(UserSession::instance().getCustomerId(), updatedData);
    if (!success) {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить данные профиля");
        return;
    }

    // Обновляем данные в сессии
    UserSession::instance().setCustomerData(
            UserSession::instance().getCustomerId(),
            name,
            email,
            phone,
            address,
            contacts
    );

    QMessageBox::information(this, "Успех", "Профиль успешно обновлён");
}

void MainWindow::open_cart_customer()
{
    int currentUserId = UserSession::instance().getCustomerId();

    if (currentUserId == -1) {
        QMessageBox::warning(this, "Ошибка", "Пользователь не авторизован");
        return;
    }

    if (cartWindow) {
        cartWindow->deleteLater();
        cartWindow = nullptr;
    }

    cartWindow = new CartWindow(requests);
    cartWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(this, &MainWindow::cartUpdated, cartWindow, &CartWindow::loadCart);

    cartWindow->show();
    cartWindow->raise();
    cartWindow->activateWindow();

    emit cartUpdated();
}



void MainWindow::open_orders_customer()
{
    int currentUserId = 1;
    QJsonArray orders = requests->getOrders(currentUserId);

    if (orders.isEmpty()) {
        QMessageBox::information(this, "Заказы", "У вас нет заказов");
        return;
    }

    initializingTable(orders);
}

void MainWindow::onAddToCartClicked()
{
    if (!UserSession::instance().isLoggedIn()) {
        QMessageBox::warning(this, "Ошибка", "Необходимо авторизоваться");
        return;
    }

    QList<QTableWidgetItem*> selected = ui->tableWidget->selectedItems();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите товар");
        return;
    }

    int row = selected.first()->row();
    int productId = ui->tableWidget->item(row, 0)->text().toInt();

    QJsonObject response = requests->addToCart(UserSession::instance().getCustomerId(), productId, 1);

    if (response.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить товар в корзину");
    } else {
        QMessageBox::information(this, "Успешно", "Товар добавлен в корзину");
        emit cartUpdated();
    }
}

void MainWindow::Exit()
{
    emit loggedOut();
}


