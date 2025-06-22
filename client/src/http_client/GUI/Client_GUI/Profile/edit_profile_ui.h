/********************************************************************************
** Form generated from reading UI file 'Change_info_form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EDIT_PROFILE_UI_H
#define EDIT_PROFILE_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *pushButton_exit;
    QLabel *label_name;
    QLabel *label_phone;
    QLabel *label_contacts;
    QLabel *label_address;
    QTextEdit *textEdit_name;
    QTextEdit *textEdit_phone;
    QTextEdit *textEdit_contacts;
    QTextEdit *textEdit_address;
    QPushButton *pushButton_apply_changes;
    QTextEdit *textEdit_email;
    QLabel *label_name_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(363, 289);
        pushButton_exit = new QPushButton(Form);
        pushButton_exit->setObjectName(QString::fromUtf8("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(10, 0, 113, 31));
        pushButton_exit->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(252, 0, 25);"));
        label_name = new QLabel(Form);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(60, 50, 41, 16));
        label_phone = new QLabel(Form);
        label_phone->setObjectName(QString::fromUtf8("label_phone"));
        label_phone->setGeometry(QRect(40, 110, 61, 16));
        label_contacts = new QLabel(Form);
        label_contacts->setObjectName(QString::fromUtf8("label_contacts"));
        label_contacts->setGeometry(QRect(10, 140, 91, 16));
        label_address = new QLabel(Form);
        label_address->setObjectName(QString::fromUtf8("label_address"));
        label_address->setGeometry(QRect(50, 170, 51, 16));
        textEdit_name = new QTextEdit(Form);
        textEdit_name->setObjectName(QString::fromUtf8("textEdit_name"));
        textEdit_name->setGeometry(QRect(100, 50, 231, 21));
        textEdit_phone = new QTextEdit(Form);
        textEdit_phone->setObjectName(QString::fromUtf8("textEdit_phone"));
        textEdit_phone->setGeometry(QRect(100, 110, 231, 21));
        textEdit_contacts = new QTextEdit(Form);
        textEdit_contacts->setObjectName(QString::fromUtf8("textEdit_contacts"));
        textEdit_contacts->setGeometry(QRect(100, 140, 231, 21));
        textEdit_address = new QTextEdit(Form);
        textEdit_address->setObjectName(QString::fromUtf8("textEdit_address"));
        textEdit_address->setGeometry(QRect(100, 170, 231, 21));
        pushButton_apply_changes = new QPushButton(Form);
        pushButton_apply_changes->setObjectName(QString::fromUtf8("pushButton_apply_changes"));
        pushButton_apply_changes->setGeometry(QRect(130, 210, 171, 41));
        pushButton_apply_changes->setStyleSheet(QString::fromUtf8("border: 2px solid black;\n"
"background-color: rgb(35, 177, 52);"));
        textEdit_email = new QTextEdit(Form);
        textEdit_email->setObjectName(QString::fromUtf8("textEdit_email"));
        textEdit_email->setGeometry(QRect(100, 80, 231, 21));
        label_name_2 = new QLabel(Form);
        label_name_2->setObjectName(QString::fromUtf8("label_name_2"));
        label_name_2->setGeometry(QRect(50, 80, 51, 20));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\321\204\320\270\320\273\321\217", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("Form", "\320\222\321\213\320\271\321\202\320\270", nullptr));
        label_name->setText(QCoreApplication::translate("Form", "\320\230\320\274\321\217:", nullptr));
        label_phone->setText(QCoreApplication::translate("Form", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        label_contacts->setText(QCoreApplication::translate("Form", "\320\236\321\200\320\263\320\260\320\275\320\270\320\267\320\260\321\206\320\270\321\217:", nullptr));
        label_address->setText(QCoreApplication::translate("Form", "\320\220\320\264\321\200\320\265\321\201:", nullptr));
        pushButton_apply_changes->setText(QCoreApplication::translate("Form", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", nullptr));
        label_name_2->setText(QCoreApplication::translate("Form", "\320\237\320\276\321\207\321\202\320\260:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // EDIT_PROFILE_UI_H
