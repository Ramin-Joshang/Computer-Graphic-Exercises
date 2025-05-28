/********************************************************************************
** Form generated from reading UI file 'welcomewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEWINDOW_H
#define UI_WELCOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *newPaintBtn;
    QPushButton *openPaintBtn;
    QLabel *label_2;

    void setupUi(QMainWindow *WelcomeWindow)
    {
        if (WelcomeWindow->objectName().isEmpty())
            WelcomeWindow->setObjectName("WelcomeWindow");
        WelcomeWindow->resize(563, 415);
        centralwidget = new QWidget(WelcomeWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 561, 411));
        label->setPixmap(QPixmap(QString::fromUtf8(":/stockes/resources/Back open.png")));
        newPaintBtn = new QPushButton(centralwidget);
        newPaintBtn->setObjectName("newPaintBtn");
        newPaintBtn->setGeometry(QRect(350, 226, 151, 31));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        newPaintBtn->setFont(font);
        newPaintBtn->setAutoFillBackground(false);
        newPaintBtn->setStyleSheet(QString::fromUtf8("background-color: black;\n"
                                                     "color: white;\n"
                                                     "border-radius: 13px;"));
        openPaintBtn = new QPushButton(centralwidget);
        openPaintBtn->setObjectName("openPaintBtn");
        openPaintBtn->setGeometry(QRect(350, 270, 151, 31));
        openPaintBtn->setFont(font);
        openPaintBtn->setStyleSheet(QString::fromUtf8("background-color: black;\n"
                                                      "color: white;\n"
                                                      "border-radius: 13px;"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(360, 80, 131, 121));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/stockes/resources/Logo.png")));
        WelcomeWindow->setCentralWidget(centralwidget);

        retranslateUi(WelcomeWindow);

        QMetaObject::connectSlotsByName(WelcomeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WelcomeWindow)
    {
        WelcomeWindow->setWindowTitle(QCoreApplication::translate("WelcomeWindow", "MainWindow", nullptr));
        label->setText(QString());
        newPaintBtn->setText(QCoreApplication::translate("WelcomeWindow", "New Painting", nullptr));
        openPaintBtn->setText(QCoreApplication::translate("WelcomeWindow", "Open Painting", nullptr));
        label_2->setText(QString());
    } // retranslateUi
};

namespace Ui
{
    class WelcomeWindow : public Ui_WelcomeWindow
    {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEWINDOW_H
