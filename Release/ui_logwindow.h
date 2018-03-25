/********************************************************************************
** Form generated from reading UI file 'logwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWINDOW_H
#define UI_LOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_LogWindow
{
public:
    QTextBrowser *textBrowser;
    QPushButton *freshButton;
    QPushButton *closeButton;

    void setupUi(QDialog *LogWindow)
    {
        if (LogWindow->objectName().isEmpty())
            LogWindow->setObjectName(QStringLiteral("LogWindow"));
        LogWindow->resize(748, 493);
        LogWindow->setMinimumSize(QSize(748, 493));
        LogWindow->setMaximumSize(QSize(748, 493));
        textBrowser = new QTextBrowser(LogWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 20, 711, 411));
        freshButton = new QPushButton(LogWindow);
        freshButton->setObjectName(QStringLiteral("freshButton"));
        freshButton->setGeometry(QRect(510, 450, 84, 28));
        closeButton = new QPushButton(LogWindow);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(630, 450, 84, 28));

        retranslateUi(LogWindow);

        QMetaObject::connectSlotsByName(LogWindow);
    } // setupUi

    void retranslateUi(QDialog *LogWindow)
    {
        LogWindow->setWindowTitle(QApplication::translate("LogWindow", "Logs", 0));
        freshButton->setText(QApplication::translate("LogWindow", "Refresh", 0));
        closeButton->setText(QApplication::translate("LogWindow", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class LogWindow: public Ui_LogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
