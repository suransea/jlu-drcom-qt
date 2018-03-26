/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionLogin_Logout;
    QAction *actionMinimize;
    QAction *actionSettings;
    QAction *actionAbout;
    QAction *actionCheck_Log;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QPushButton *loginButton;
    QPushButton *minButton;
    QLineEdit *nameEdit;
    QLineEdit *passwdEdit;
    QMenuBar *menuBar;
    QMenu *menuDrcom_client;
    QMenu *menuOption;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(465, 233);
        MainWindow->setMinimumSize(QSize(465, 233));
        MainWindow->setMaximumSize(QSize(465, 233));
        QIcon icon;
        icon.addFile(QStringLiteral(":/png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setIconSize(QSize(128, 128));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionLogin_Logout = new QAction(MainWindow);
        actionLogin_Logout->setObjectName(QStringLiteral("actionLogin_Logout"));
        actionMinimize = new QAction(MainWindow);
        actionMinimize->setObjectName(QStringLiteral("actionMinimize"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCheck_Log = new QAction(MainWindow);
        actionCheck_Log->setObjectName(QStringLiteral("actionCheck_Log"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 30, 71, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 70, 71, 20));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(100, 110, 201, 26));
        checkBox->setFocusPolicy(Qt::NoFocus);
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(250, 110, 191, 26));
        checkBox_2->setFocusPolicy(Qt::NoFocus);
        loginButton = new QPushButton(centralWidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(120, 150, 84, 28));
        loginButton->setFocusPolicy(Qt::TabFocus);
        loginButton->setLayoutDirection(Qt::LeftToRight);
        minButton = new QPushButton(centralWidget);
        minButton->setObjectName(QStringLiteral("minButton"));
        minButton->setGeometry(QRect(250, 150, 84, 28));
        minButton->setFocusPolicy(Qt::TabFocus);
        minButton->setLayoutDirection(Qt::LeftToRight);
        nameEdit = new QLineEdit(centralWidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));
        nameEdit->setGeometry(QRect(180, 20, 181, 28));
        nameEdit->setFocusPolicy(Qt::StrongFocus);
        passwdEdit = new QLineEdit(centralWidget);
        passwdEdit->setObjectName(QStringLiteral("passwdEdit"));
        passwdEdit->setGeometry(QRect(180, 60, 181, 28));
        passwdEdit->setFocusPolicy(Qt::StrongFocus);
        passwdEdit->setEchoMode(QLineEdit::Password);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 465, 25));
        menuDrcom_client = new QMenu(menuBar);
        menuDrcom_client->setObjectName(QStringLiteral("menuDrcom_client"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDrcom_client->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuDrcom_client->addAction(actionLogin_Logout);
        menuDrcom_client->addAction(actionMinimize);
        menuDrcom_client->addAction(actionExit);
        menuOption->addAction(actionSettings);
        menuOption->addAction(actionCheck_Log);
        menuOption->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Drcom Client", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Esc", 0));
        actionLogin_Logout->setText(QApplication::translate("MainWindow", "Login / Logout", 0));
        actionLogin_Logout->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", 0));
        actionMinimize->setText(QApplication::translate("MainWindow", "Minimize", 0));
        actionMinimize->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
        actionSettings->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionCheck_Log->setText(QApplication::translate("MainWindow", "Check Log", 0));
        actionCheck_Log->setShortcut(QApplication::translate("MainWindow", "Ctrl+Alt+L", 0));
        label->setText(QApplication::translate("MainWindow", "Username:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Password:", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Remember Me", 0));
        checkBox_2->setText(QApplication::translate("MainWindow", "Auto Login", 0));
        loginButton->setText(QApplication::translate("MainWindow", "Login", 0));
        minButton->setText(QApplication::translate("MainWindow", "Minimize", 0));
        menuDrcom_client->setTitle(QApplication::translate("MainWindow", "Action", 0));
        menuOption->setTitle(QApplication::translate("MainWindow", "Option", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
