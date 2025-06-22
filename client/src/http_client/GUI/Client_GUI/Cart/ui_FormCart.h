/********************************************************************************
** Form generated from reading UI file 'Form_cart.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCART_H
#define UI_FORMCART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_cart
{
public:
    QPushButton *pushButton_exit;
    QPushButton *pushButton_order;
    QTableView *tableView;
    QPushButton *pushButton_order_2;

    void setupUi(QWidget *Form_cart)
    {
        if (Form_cart->objectName().isEmpty())
            Form_cart->setObjectName(QString::fromUtf8("Form_cart"));
        Form_cart->resize(654, 371);
        Form_cart->setStyleSheet(QString::fromUtf8(""));
        pushButton_exit = new QPushButton(Form_cart);
        pushButton_exit->setObjectName(QString::fromUtf8("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(530, 10, 113, 32));
        pushButton_exit->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(252, 0, 15);"));
        pushButton_order = new QPushButton(Form_cart);
        pushButton_order->setObjectName(QString::fromUtf8("pushButton_order"));
        pushButton_order->setGeometry(QRect(10, 310, 113, 31));
        pushButton_order->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(22, 170, 2);"));
        tableView = new QTableView(Form_cart);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(10, 50, 631, 251));
        tableView->setStyleSheet(QString::fromUtf8(""));
        pushButton_order_2 = new QPushButton(Form_cart);
        pushButton_order_2->setObjectName(QString::fromUtf8("pushButton_order_2"));
        pushButton_order_2->setGeometry(QRect(140, 310, 151, 31));
        pushButton_order_2->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(252, 0, 16);"));

        retranslateUi(Form_cart);

        QMetaObject::connectSlotsByName(Form_cart);
    } // setupUi

    void retranslateUi(QWidget *Form_cart)
    {
        Form_cart->setWindowTitle(QCoreApplication::translate("Form_cart", "\320\232\320\276\321\200\320\267\320\270\320\275\320\260", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("Form_cart", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        pushButton_order->setText(QCoreApplication::translate("Form_cart", "\320\227\320\260\320\272\320\260\320\267\320\260\321\202\321\214", nullptr));
        pushButton_order_2->setText(QCoreApplication::translate("Form_cart", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\272\320\276\321\200\320\267\320\270\320\275\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form_cart: public Ui_Form_cart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCART_H
