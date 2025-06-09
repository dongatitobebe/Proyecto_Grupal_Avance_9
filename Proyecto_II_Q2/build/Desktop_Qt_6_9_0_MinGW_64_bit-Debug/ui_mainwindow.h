/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *B_Jugar;
    QPushButton *B_NuevoJuego;
    QPushButton *B_SalirJuego;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        B_Jugar = new QPushButton(centralwidget);
        B_Jugar->setObjectName("B_Jugar");
        B_Jugar->setGeometry(QRect(292, 198, 191, 41));
        B_NuevoJuego = new QPushButton(centralwidget);
        B_NuevoJuego->setObjectName("B_NuevoJuego");
        B_NuevoJuego->setGeometry(QRect(292, 268, 191, 41));
        B_SalirJuego = new QPushButton(centralwidget);
        B_SalirJuego->setObjectName("B_SalirJuego");
        B_SalirJuego->setGeometry(QRect(290, 330, 191, 41));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 60, 361, 81));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Black")});
        font.setPointSize(14);
        label->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        B_Jugar->setText(QCoreApplication::translate("MainWindow", "Jugar", nullptr));
        B_NuevoJuego->setText(QCoreApplication::translate("MainWindow", "Crear Nuevo Juego", nullptr));
        B_SalirJuego->setText(QCoreApplication::translate("MainWindow", "Salir del Juego", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Eterium: El Equilibrio Roto ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
