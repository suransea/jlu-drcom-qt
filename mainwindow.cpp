#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkInterface>
#include <QList>

#include "configmapper.h"
#include "settingdialog.h"
#include "aboutdialog.h"
#include "logdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto &&config = ConfigMapper::instance;
    if (config["remember"] == "true")
    {
        ui->nameEdit->setText(config["name"]);
        ui->passwdEdit->setText(config["passwd"]);
        ui->checkBox->setChecked(true);
    }
    if (config["auto"] == "true")
    {
        ui->checkBox_2->setChecked(true);
    }
}

bool MainWindow::event(QEvent *e)
{
    if (e->type() == QEvent::WindowActivate)
    {
        auto &&config = ConfigMapper::instance;
        if (config["auto"] == "true")
        {
            on_loginButton_clicked();
        }
    }
    return QMainWindow::event(e);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString password = ui->passwdEdit->text();
    if (name == "" || password == "")
    {
        QMessageBox::information(this, "Warn", "Please Fill the Blank.", QMessageBox::Ok);
        return;
    }
    if (loginned)
    {
        drcom.logout();
        ui->loginButton->setText("login");
        ui->nameEdit->setEnabled(true);
        ui->passwdEdit->setEnabled(true);
        ui->checkBox->setEnabled(true);
        ui->checkBox_2->setEnabled(true);
        loginned = false;
    }
    else
    {
        ui->loginButton->setText("logining...");
        ui->nameEdit->setEnabled(false);
        ui->passwdEdit->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
        loginned = true;
        bool rememberStatus = ui->checkBox->isChecked();
        bool autoStatus = ui->checkBox_2->isChecked();
        auto &&config = ConfigMapper::instance;
        config.set("remember", rememberStatus ? "true" : "false");
        config.set("auto", autoStatus ? "true" : "false");
        if (rememberStatus)
        {
            config.set("name", name);
            config.set("passwd", password);
        }
        else
        {
            config.set("name", "");
            config.set("passwd", "");
        }
        config.flush();

        drcom.login(name, password);
    }
}

void MainWindow::on_loginSuccess()
{
    ui->loginButton->setText("logout");
    auto &&config = ConfigMapper::instance;
    if (config["automin"] == "true")
    {
        on_minButton_clicked();
    }
}

void MainWindow::on_loginFailed(const QString &msg)
{
    QMessageBox::information(this, "Error", msg, QMessageBox::Ok);
    ui->loginButton->setText("login");
    on_loginButton_clicked();
}

void MainWindow::on_minButton_clicked()
{
    this->hide();
    auto &&config = ConfigMapper::instance;
    if (config["tray"] == "false")
    {
        return;
    }
    auto systemTrayIcon = new QSystemTrayIcon();
    QIcon icon = QIcon(":/png");
    systemTrayIcon->setToolTip("drcom-client");
    systemTrayIcon->setIcon(icon);
    auto trayActionExit = new QAction("Exit", this);
    auto trayActionShow = new QAction("Show Main", this);
    connect(trayActionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
    connect(trayActionShow, &QAction::triggered, [this, systemTrayIcon] {
        this->show();
        systemTrayIcon->hide();
        delete systemTrayIcon;
    });
    auto trayMenu = new QMenu(this);
    trayMenu->addAction(trayActionShow);
    trayMenu->addAction(trayActionExit);
    systemTrayIcon->setContextMenu(trayMenu);
    connect(systemTrayIcon, &QSystemTrayIcon::destroyed, [=] {
        delete trayMenu;
        delete trayActionExit;
        delete trayActionShow;
    });
    connect(systemTrayIcon, &QSystemTrayIcon::activated, [this, systemTrayIcon](QSystemTrayIcon::ActivationReason reason) {
        switch (reason)
        {
        case QSystemTrayIcon::Trigger:
            this->show();
            systemTrayIcon->hide();
            delete systemTrayIcon;
            break;
        case QSystemTrayIcon::DoubleClick:
            systemTrayIcon->hide();
            delete systemTrayIcon;
            break;
        default:
            break;
        }
    });
    systemTrayIcon->show();
}

void MainWindow::on_actionExit_triggered()
{
    drcom.logout();
    exit(0);
}

void MainWindow::on_actionLogin_Logout_triggered()
{
    on_loginButton_clicked();
}

void MainWindow::on_actionMinimize_triggered()
{
    on_minButton_clicked();
}

void MainWindow::on_checkBox_stateChanged(int state)
{
    if (Qt::Unchecked == state)
    {
        if (ui->checkBox_2->isChecked())
        {
            ui->checkBox_2->setChecked(false);
        }
    }
}

void MainWindow::on_checkBox_2_stateChanged(int state)
{
    if (Qt::Checked == state)
    {
        if (!ui->checkBox->isChecked())
        {
            ui->checkBox->setChecked(true);
        }
    }
}

void MainWindow::on_actionSettings_triggered()
{
    auto settingsWindow = new SettingDialog(this);
    connect(settingsWindow, &SettingDialog::finished, [settingsWindow](int) {
        delete settingsWindow;
    });
    settingsWindow->show();
}

void MainWindow::on_actionAbout_triggered()
{
    auto aboutWindow = new AboutDialog(this);
    connect(aboutWindow, &AboutDialog::finished, [aboutWindow](int) {
        delete aboutWindow;
    });
    aboutWindow->show();
}

void MainWindow::on_actionCheck_Log_triggered()
{
    auto logWindow = new LogDialog(this);
    connect(logWindow, &LogDialog::finished, [logWindow](int) {
        delete logWindow;
    });
    logWindow->show();
}
