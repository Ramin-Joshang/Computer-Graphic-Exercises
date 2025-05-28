/********************************************************************************
** Form generated from reading UI file 'messagedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEDIALOG_H
#define UI_MESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_messageDialog
{
public:
    QLabel *background;
    QPushButton *yesBtn;
    QLabel *message;
    QPushButton *noBtn;
    QLabel *messageup;
    QPushButton *closeBtn;

    void setupUi(QDialog *messageDialog)
    {
        if (messageDialog->objectName().isEmpty())
            messageDialog->setObjectName("messageDialog");
        messageDialog->resize(509, 266);
        background = new QLabel(messageDialog);
        background->setObjectName("background");
        background->setGeometry(QRect(50, 40, 407, 181));
        background->setStyleSheet(QString::fromUtf8("background-image: url(:/stockes/resources/MessageboxFinal.png);"));
        yesBtn = new QPushButton(messageDialog);
        yesBtn->setObjectName("yesBtn");
        yesBtn->setGeometry(QRect(140, 160, 111, 41));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        yesBtn->setFont(font);
        yesBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        yesBtn->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"color: black;\n"
"border-radius: 20px;\n"
"font: 11pt \"Montserrat\";"));
        message = new QLabel(messageDialog);
        message->setObjectName("message");
        message->setGeometry(QRect(50, 88, 411, 61));
        message->setFont(font);
        message->setStyleSheet(QString::fromUtf8(" text-align: center;\n"
"color: #000;\n"
"font: 11pt \"Montserrat\";"));
        message->setAlignment(Qt::AlignCenter);
        noBtn = new QPushButton(messageDialog);
        noBtn->setObjectName("noBtn");
        noBtn->setGeometry(QRect(270, 160, 111, 41));
        noBtn->setFont(font);
        noBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        noBtn->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"color: black;\n"
"border-radius: 20px;\n"
"font: 11pt \"Montserrat\";"));
        messageup = new QLabel(messageDialog);
        messageup->setObjectName("messageup");
        messageup->setGeometry(QRect(70, 57, 201, 16));
        QFont font1;
        font1.setPointSize(11);
        messageup->setFont(font1);
        closeBtn = new QPushButton(messageDialog);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setGeometry(QRect(419, 54, 20, 21));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closeBtn->sizePolicy().hasHeightForWidth());
        closeBtn->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(21);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setKerning(false);
        closeBtn->setFont(font2);
        closeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        closeBtn->setLayoutDirection(Qt::LeftToRight);
        closeBtn->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"color: #710101;\n"
"text-align: left;\n"
"font: 21pt \"IROicons\";"));
        closeBtn->setCheckable(false);
        closeBtn->setFlat(false);

        retranslateUi(messageDialog);

        closeBtn->setDefault(false);


        QMetaObject::connectSlotsByName(messageDialog);
    } // setupUi

    void retranslateUi(QDialog *messageDialog)
    {
        messageDialog->setWindowTitle(QCoreApplication::translate("messageDialog", "Dialog", nullptr));
        background->setText(QString());
        yesBtn->setText(QCoreApplication::translate("messageDialog", "YES", nullptr));
        message->setText(QCoreApplication::translate("messageDialog", "Are you sure you want to\n"
"stop being creative and save your work?", nullptr));
        noBtn->setText(QCoreApplication::translate("messageDialog", "No", nullptr));
        messageup->setText(QCoreApplication::translate("messageDialog", "IRO Paint Developers say", nullptr));
        closeBtn->setText(QCoreApplication::translate("messageDialog", "x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messageDialog: public Ui_messageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEDIALOG_H
