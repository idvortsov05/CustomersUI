/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowCustomer
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_Change_info_user;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_cart;
    QPushButton *pushButton_find_products;
    QTextEdit *textEdit_find_product;
    QLabel *label_find;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *pushButton_orders;
    QPushButton *pushButton_reset_filters;
    QTableWidget *tableWidget;
    QPushButton *pushButton_sort_products;
    QPushButton *pushButton_add_to_cart;

    void setupUi(QMainWindow *MainWindowCustomer)
    {
        if (MainWindowCustomer->objectName().isEmpty())
            MainWindowCustomer->setObjectName(QString::fromUtf8("MainWindowCustomer"));
        MainWindowCustomer->resize(1109, 676);
        MainWindowCustomer->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindowCustomer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_Change_info_user = new QPushButton(centralwidget);
        pushButton_Change_info_user->setObjectName(QString::fromUtf8("pushButton_Change_info_user"));
        pushButton_Change_info_user->setGeometry(QRect(860, 60, 161, 31));
        pushButton_Change_info_user->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(215, 215, 215);"));
        pushButton_exit = new QPushButton(centralwidget);
        pushButton_exit->setObjectName(QString::fromUtf8("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(860, 10, 161, 31));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        pushButton_exit->setFont(font);
        pushButton_exit->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 0, 40);\n"
"border: 2px solid black;"));
        pushButton_cart = new QPushButton(centralwidget);
        pushButton_cart->setObjectName(QString::fromUtf8("pushButton_cart"));
        pushButton_cart->setGeometry(QRect(10, 20, 161, 31));
        pushButton_cart->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(215, 215, 215);"));
        pushButton_find_products = new QPushButton(centralwidget);
        pushButton_find_products->setObjectName(QString::fromUtf8("pushButton_find_products"));
        pushButton_find_products->setGeometry(QRect(230, 290, 131, 31));
        QFont font1;
        font1.setPointSize(13);
        pushButton_find_products->setFont(font1);
        pushButton_find_products->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(0, 228, 58)}\n"
"QPushButton{border: 2px solid black}"));
        textEdit_find_product = new QTextEdit(centralwidget);
        textEdit_find_product->setObjectName(QString::fromUtf8("textEdit_find_product"));
        textEdit_find_product->setGeometry(QRect(20, 290, 201, 31));
        textEdit_find_product->setStyleSheet(QString::fromUtf8("QTextEdit{border: 1px solid black}"));
        label_find = new QLabel(centralwidget);
        label_find->setObjectName(QString::fromUtf8("label_find"));
        label_find->setGeometry(QRect(20, 270, 191, 16));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_find->setFont(font2);
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 150, 241, 31));
        comboBox->setFont(font2);
        comboBox->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 130, 251, 16));
        label->setFont(font2);
        pushButton_orders = new QPushButton(centralwidget);
        pushButton_orders->setObjectName(QString::fromUtf8("pushButton_orders"));
        pushButton_orders->setGeometry(QRect(10, 60, 161, 31));
        pushButton_orders->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(215, 215, 215);"));
        pushButton_reset_filters = new QPushButton(centralwidget);
        pushButton_reset_filters->setObjectName(QString::fromUtf8("pushButton_reset_filters"));
        pushButton_reset_filters->setGeometry(QRect(380, 290, 131, 31));
        pushButton_reset_filters->setFont(font1);
        pushButton_reset_filters->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgb(248, 30, 20)}\n"
"QPushButton{border: 2px solid black}"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 330, 1051, 291));
        pushButton_sort_products = new QPushButton(centralwidget);
        pushButton_sort_products->setObjectName(QString::fromUtf8("pushButton_sort_products"));
        pushButton_sort_products->setGeometry(QRect(260, 150, 131, 31));
        pushButton_sort_products->setFont(font1);
        pushButton_sort_products->setStyleSheet(QString::fromUtf8("background-color: rgb(215, 215, 215);\n"
"border: 2px solid black;"));
        pushButton_add_to_cart = new QPushButton(centralwidget);
        pushButton_add_to_cart->setObjectName(QString::fromUtf8("pushButton_add_to_cart"));
        pushButton_add_to_cart->setGeometry(QRect(520, 290, 141, 31));
        pushButton_add_to_cart->setFont(font1);
        pushButton_add_to_cart->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 153, 18);\n"
"border: 2px solid black;"));
        MainWindowCustomer->setCentralWidget(centralwidget);

        retranslateUi(MainWindowCustomer);

        QMetaObject::connectSlotsByName(MainWindowCustomer);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowCustomer)
    {
        MainWindowCustomer->setWindowTitle(QCoreApplication::translate("MainWindowCustomer", "\320\244\320\276\321\200\320\274\320\260 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        pushButton_Change_info_user->setText(QCoreApplication::translate("MainWindowCustomer", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\321\200\320\276\321\204\320\270\320\273\321\214", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("MainWindowCustomer", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\277\321\200\320\276\321\204\320\270\320\273\321\217", nullptr));
        pushButton_cart->setText(QCoreApplication::translate("MainWindowCustomer", "\320\232\320\276\321\200\320\267\320\270\320\275\320\260", nullptr));
        pushButton_find_products->setText(QCoreApplication::translate("MainWindowCustomer", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        label_find->setText(QCoreApplication::translate("MainWindowCustomer", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\272\321\200\320\270\321\202\320\265\321\200\320\270\320\270 \320\277\320\276\320\270\321\201\320\272\320\260:", nullptr));
        label->setText(QCoreApplication::translate("MainWindowCustomer", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \320\272\321\200\320\270\321\202\320\265\321\200\320\270\320\271 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\270:", nullptr));
        pushButton_orders->setText(QCoreApplication::translate("MainWindowCustomer", "\320\227\320\260\320\272\320\260\320\267\321\213", nullptr));
        pushButton_reset_filters->setText(QCoreApplication::translate("MainWindowCustomer", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindowCustomer", "id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindowCustomer", "photo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindowCustomer", "name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindowCustomer", "optprice", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindowCustomer", "roznprice", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindowCustomer", "description", nullptr));
        pushButton_sort_products->setText(QCoreApplication::translate("MainWindowCustomer", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        pushButton_add_to_cart->setText(QCoreApplication::translate("MainWindowCustomer", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262 \320\272\320\276\321\200\320\267\320\270\320\275\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowCustomer: public Ui_MainWindowCustomer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
