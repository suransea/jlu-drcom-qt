/********************************************************************************
** Form generated from reading UI file 'aboutwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QStringLiteral("AboutWindow"));
        AboutWindow->resize(488, 269);
        AboutWindow->setMinimumSize(QSize(488, 269));
        AboutWindow->setMaximumSize(QSize(488, 269));
        buttonBox = new QDialogButtonBox(AboutWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(120, 220, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        label = new QLabel(AboutWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 128, 128));
        label->setPixmap(QPixmap(QString::fromUtf8(":/png")));
        textBrowser = new QTextBrowser(AboutWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(170, 20, 291, 191));

        retranslateUi(AboutWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AboutWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QDialog *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "About", 0));
        label->setText(QString());
        textBrowser->setHtml(QApplication::translate("AboutWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">Drcom Client - Qt Edition</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">Version 0.1</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\""
                        " font-size:12pt;\">Build by sea in 2018/3/22.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">contact: simpleslight@outlook.com</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\273\205\344\276\233\345\255\246\344\271\240\344\272\244\346\265\201\344\275\277\347\224\250\343\200\202</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
