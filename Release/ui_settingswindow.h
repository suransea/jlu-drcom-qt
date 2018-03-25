/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *showTrayCheckBox;
    QCheckBox *autoMinCheckBox;
    QLineEdit *macEdit;
    QLineEdit *serverEdit;

    void setupUi(QDialog *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->resize(442, 256);
        SettingsWindow->setMinimumSize(QSize(442, 256));
        SettingsWindow->setMaximumSize(QSize(442, 256));
        buttonBox = new QDialogButtonBox(SettingsWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(80, 200, 341, 32));
        buttonBox->setFocusPolicy(Qt::NoFocus);
        buttonBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        buttonBox->setCenterButtons(false);
        label = new QLabel(SettingsWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 91, 20));
        label_2 = new QLabel(SettingsWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 70, 63, 20));
        showTrayCheckBox = new QCheckBox(SettingsWindow);
        showTrayCheckBox->setObjectName(QStringLiteral("showTrayCheckBox"));
        showTrayCheckBox->setGeometry(QRect(70, 110, 361, 26));
        showTrayCheckBox->setFocusPolicy(Qt::NoFocus);
        autoMinCheckBox = new QCheckBox(SettingsWindow);
        autoMinCheckBox->setObjectName(QStringLiteral("autoMinCheckBox"));
        autoMinCheckBox->setGeometry(QRect(70, 150, 361, 26));
        autoMinCheckBox->setFocusPolicy(Qt::NoFocus);
        macEdit = new QLineEdit(SettingsWindow);
        macEdit->setObjectName(QStringLiteral("macEdit"));
        macEdit->setGeometry(QRect(180, 20, 191, 28));
        serverEdit = new QLineEdit(SettingsWindow);
        serverEdit->setObjectName(QStringLiteral("serverEdit"));
        serverEdit->setGeometry(QRect(180, 60, 191, 28));

        retranslateUi(SettingsWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "Settings", 0));
        label->setText(QApplication::translate("SettingsWindow", "Mac Adress:", 0));
        label_2->setText(QApplication::translate("SettingsWindow", "Sever IP:", 0));
        showTrayCheckBox->setText(QApplication::translate("SettingsWindow", "Show Tray Icon at Minimize Mode", 0));
        autoMinCheckBox->setText(QApplication::translate("SettingsWindow", "Auto Minimize after Loginer Successfully", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
