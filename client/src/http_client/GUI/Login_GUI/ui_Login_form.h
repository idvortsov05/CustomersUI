/********************************************************************************
** Form generated from reading UI file 'Login_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_FORM_H
#define UI_LOGIN_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_login_window
{
public:
    QLabel *label_login;
    QLabel *label_password;
    QTextEdit *textEdit_login;
    QTextEdit *textEdit_password;
    QPushButton *pushButton_login;
    QPushButton *pushButton_register;
    QLabel *label;

    void setupUi(QDialog *login_window)
    {
        if (login_window->objectName().isEmpty())
            login_window->setObjectName(QString::fromUtf8("login_window"));
        login_window->resize(291, 289);
        label_login = new QLabel(login_window);
        label_login->setObjectName(QString::fromUtf8("label_login"));
        label_login->setGeometry(QRect(0, 50, 67, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_login->setFont(font);
        label_password = new QLabel(login_window);
        label_password->setObjectName(QString::fromUtf8("label_password"));
        label_password->setGeometry(QRect(0, 110, 67, 17));
        label_password->setFont(font);
        textEdit_login = new QTextEdit(login_window);
        textEdit_login->setObjectName(QString::fromUtf8("textEdit_login"));
        textEdit_login->setGeometry(QRect(60, 50, 191, 31));
        textEdit_password = new QTextEdit(login_window);
        textEdit_password->setObjectName(QString::fromUtf8("textEdit_password"));
        textEdit_password->setGeometry(QRect(60, 100, 191, 31));
        pushButton_login = new QPushButton(login_window);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(70, 150, 171, 21));
        pushButton_login->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 174, 46);\n"
"border: 2px solid black;"));
        pushButton_register = new QPushButton(login_window);
        pushButton_register->setObjectName(QString::fromUtf8("pushButton_register"));
        pushButton_register->setGeometry(QRect(70, 190, 171, 21));
        pushButton_register->setStyleSheet(QString::fromUtf8("background-color: rgb(126, 145, 255);\n"
"border: 2px solid black;"));
        label = new QLabel(login_window);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 170, 31, 21));
        label->setFont(font);

        retranslateUi(login_window);

        QMetaObject::connectSlotsByName(login_window);
    } // setupUi

    void retranslateUi(QDialog *login_window)
    {
        login_window->setWindowTitle(QCoreApplication::translate("login_window", "\320\236\320\272\320\275\320\276 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        label_login->setText(QCoreApplication::translate("login_window", " \320\233\320\276\320\263\320\270\320\275:", nullptr));
        label_password->setText(QCoreApplication::translate("login_window", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        pushButton_login->setText(QCoreApplication::translate("login_window", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        pushButton_register->setText(QCoreApplication::translate("login_window", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        label->setText(QCoreApplication::translate("login_window", "\320\270\320\273\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login_window: public Ui_login_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_FORM_H
