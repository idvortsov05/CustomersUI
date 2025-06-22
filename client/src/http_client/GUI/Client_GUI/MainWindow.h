#ifndef HTTP_CLIENT_CLIENT_FORM_H
#define HTTP_CLIENT_CLIENT_FORM_H

#include <QTableWidgetItem>
#include "http_client/http_requests/Requests.h"
#include "ui_MainWindow.h"
#include "../Client_GUI/Profile/EditProfileWindow.h"
#include "../Client_GUI/Cart/CartWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void edit_profile(); // слот для изменения профиля
    void onAddToCartClicked();
    void cartUpdated() {};
    void open_cart_customer(); // слот для открытия корзины
    void open_orders_customer(); // слот для открытия заказов
    void ResetFilters(); // слот для сброса фильтров
    void FindProducts(); // слот для поиска товаров по фильтрам или поиску
    void SortProducts(); // слот для сортировки
    void Exit(); // слот для выхода из программы
    void handleProfileUpdate(const QString &name,
                             const QString &phone,
                             const QString &contacts,
                             const QString &address,
                             const QString &email);

signals:
    void loggedOut();

private:
    EditProfileWindow *editProfileWindow;
    Ui_MainWindowCustomer *ui;
    CartWindow* cartWindow = nullptr;
    Requests *requests;

    QString currentSortField;

    void updateTable();
    void initializingTable(const QJsonArray &);
    void setupConnections();
    QTableWidgetItem* createPhotoTableItem(const QString &base64String, int newSize);
};

#endif //HTTP_CLIENT_CLIENT_FORM_H
