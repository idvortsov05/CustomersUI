/********************************************************************************
** Form generated from reading UI file 'RegisterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QLabel *label;
    QLineEdit *lineEdit_name;
    QLabel *label_3;
    QLineEdit *lineEdit_email;
    QLabel *label_4;
    QLineEdit *lineEdit_phone;
    QLabel *label_5;
    QLineEdit *lineEdit_address;
    QLabel *label_6;
    QLineEdit *lineEdit_contact;
    QLineEdit *lineEdit_password;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QString::fromUtf8("RegisterDialog"));
        RegisterDialog->resize(431, 364);
        label = new QLabel(RegisterDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 40, 31, 16));
        lineEdit_name = new QLineEdit(RegisterDialog);
        lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(160, 40, 191, 21));
        label_3 = new QLabel(RegisterDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 70, 41, 16));
        lineEdit_email = new QLineEdit(RegisterDialog);
        lineEdit_email->setObjectName(QString::fromUtf8("lineEdit_email"));
        lineEdit_email->setGeometry(QRect(160, 70, 191, 21));
        label_4 = new QLabel(RegisterDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 100, 61, 20));
        lineEdit_phone = new QLineEdit(RegisterDialog);
        lineEdit_phone->setObjectName(QString::fromUtf8("lineEdit_phone"));
        lineEdit_phone->setGeometry(QRect(160, 100, 191, 21));
        label_5 = new QLabel(RegisterDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(110, 130, 51, 20));
        lineEdit_address = new QLineEdit(RegisterDialog);
        lineEdit_address->setObjectName(QString::fromUtf8("lineEdit_address"));
        lineEdit_address->setGeometry(QRect(160, 130, 191, 21));
        label_6 = new QLabel(RegisterDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 160, 91, 20));
        lineEdit_contact = new QLineEdit(RegisterDialog);
        lineEdit_contact->setObjectName(QString::fromUtf8("lineEdit_contact"));
        lineEdit_contact->setGeometry(QRect(160, 160, 191, 21));
        lineEdit_password = new QLineEdit(RegisterDialog);
        lineEdit_password->setObjectName(QString::fromUtf8("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(160, 190, 191, 21));
        label_7 = new QLabel(RegisterDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(100, 190, 61, 20));
        label_8 = new QLabel(RegisterDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(60, 230, 101, 20));
        pushButton = new QPushButton(RegisterDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 230, 191, 51));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(37, 167, 30);"));

        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "\320\236\320\272\320\275\320\276 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\320\270", nullptr));
        label->setText(QCoreApplication::translate("RegisterDialog", "\320\230\320\274\321\217:", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterDialog", "\320\237\320\276\321\207\321\202\320\260:", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterDialog", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        label_5->setText(QCoreApplication::translate("RegisterDialog", "\320\220\320\264\321\200\320\265\321\201:", nullptr));
        label_6->setText(QCoreApplication::translate("RegisterDialog", "\320\236\321\200\320\263\320\260\320\275\320\270\320\267\320\260\321\206\320\270\321\217:", nullptr));
        label_7->setText(QCoreApplication::translate("RegisterDialog", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        label_8->setText(QString());
        pushButton->setText(QCoreApplication::translate("RegisterDialog", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
