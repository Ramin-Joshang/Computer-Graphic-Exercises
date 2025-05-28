/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_about
{
public:
    QLabel *background;
    QPushButton *closeBtn;
    QLabel *messageup;
    QLabel *logo;
    QLabel *maintxt;
    QLabel *dept;

    void setupUi(QDialog *about)
    {
        if (about->objectName().isEmpty())
            about->setObjectName("about");
        about->resize(616, 602);
        background = new QLabel(about);
        background->setObjectName("background");
        background->setGeometry(QRect(0, 0, 621, 601));
        background->setStyleSheet(QString::fromUtf8("background-image: url(:/stockes/resources/about back.png);"));
        closeBtn = new QPushButton(about);
        closeBtn->setObjectName("closeBtn");
        closeBtn->setGeometry(QRect(577, 15, 20, 21));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(closeBtn->sizePolicy().hasHeightForWidth());
        closeBtn->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(21);
        font.setBold(false);
        font.setItalic(false);
        font.setKerning(false);
        closeBtn->setFont(font);
        closeBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        closeBtn->setLayoutDirection(Qt::LeftToRight);
        closeBtn->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"color: #710101;\n"
"text-align: left;\n"
"font: 21pt \"IROicons\";"));
        closeBtn->setCheckable(false);
        closeBtn->setFlat(false);
        messageup = new QLabel(about);
        messageup->setObjectName("messageup");
        messageup->setGeometry(QRect(20, 17, 201, 16));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Montserrat Light")});
        font1.setPointSize(11);
        messageup->setFont(font1);
        logo = new QLabel(about);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(240, 70, 141, 171));
        logo->setStyleSheet(QString::fromUtf8("background-image: url(:/stockes/resources/about logo.png);"));
        maintxt = new QLabel(about);
        maintxt->setObjectName("maintxt");
        maintxt->setGeometry(QRect(14, 280, 641, 261));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Montserrat")});
        font2.setPointSize(11);
        maintxt->setFont(font2);
        dept = new QLabel(about);
        dept->setObjectName("dept");
        dept->setGeometry(QRect(90, 570, 441, 21));
        QFont font3;
        font3.setPointSize(11);
        dept->setFont(font3);

        retranslateUi(about);

        closeBtn->setDefault(false);


        QMetaObject::connectSlotsByName(about);
    } // setupUi

    void retranslateUi(QDialog *about)
    {
        about->setWindowTitle(QCoreApplication::translate("about", "Dialog", nullptr));
        background->setText(QString());
        closeBtn->setText(QCoreApplication::translate("about", "x", nullptr));
        messageup->setText(QCoreApplication::translate("about", "About IRO Paint", nullptr));
        logo->setText(QString());
        maintxt->setText(QCoreApplication::translate("about", "IRO Paint Version 1.0 (Build 2021-2022)\n"
"Copyrights \302\251 2022 Team 01.  all rights reserved\n"
"Bulid by QT Creator 6.0.1 (Open Source)\n"
"\n"
"IRO Paint desktop application & its user interface are protected by\n"
"trademarkand other pending or existing intellectual property rights in Egypt\n"
"and other countires (Joking guys, we are not  Microsoft, you can use\n"
"IRO Paint under the GNU General Public License)\n"
"\n"
"IRO Paint Developers:\n"
"1- Kamel Mohamed (EGY) 		4- Romaisaa El Saidy (EGY)\n"
"2- Youssef Shaaban (EGY)		5- Dina Khalid (EGY)\n"
"3- Ibrahim Mohamed (EGY)		6- Ahmed El Sarta (EGY)", nullptr));
        dept->setText(QCoreApplication::translate("about", "Systems & Biomedical Engineering Dept, Cairo University", nullptr));
    } // retranslateUi

};

namespace Ui {
    class about: public Ui_about {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
