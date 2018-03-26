#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkInterface>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginThread.reset(nullptr);
    auto cfg=configureReader.getCfg();
    if(cfg["remember"]=="true"){
        ui->nameEdit->setText(QString::fromStdString(cfg["name"]));
        ui->passwdEdit->setText(QString::fromStdString(cfg["passwd"]));
        ui->checkBox->setChecked(true);
    }
    if(cfg["auto"]=="true"){
        ui->checkBox_2->setChecked(true);
    }
}

void MainWindow::init()
{
    auto cfg=configureReader.getCfg();
    if(cfg["first_run"]=="true"){
        QList<QNetworkInterface> nets=QNetworkInterface::allInterfaces();
        for(auto &net:nets){
            if(net.flags().testFlag(QNetworkInterface::IsUp)&&
                    net.flags().testFlag(QNetworkInterface::IsRunning)&&
                    !net.flags().testFlag(QNetworkInterface::IsLoopBack)){
                configureReader.setCfg("mac",net.hardwareAddress().toStdString());
                configureReader.setCfg("first_run","false");
                configureReader.fresh();
            }
        }
    }
    if(cfg["auto"]=="true"){
        on_loginButton_clicked();
    }
}

ConfigureReader MainWindow::configureReader=ConfigureReader("drcom-client.conf");

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QString name=ui->nameEdit->text();
    QString password=ui->passwdEdit->text();
    if(name==""||password==""){
        QMessageBox::information(this,"Warn",
                                 "Please Fill the Blank.",
                                 QMessageBox::Ok);
        return;
    }
    if(loginStatus){
        loginThread->setExitFlagTrue();
        ui->loginButton->setText("login");
        ui->nameEdit->setEnabled(true);
        ui->passwdEdit->setEnabled(true);
        ui->checkBox->setEnabled(true);
        ui->checkBox_2->setEnabled(true);
        loginStatus=false;
    }else{
        ui->loginButton->setText("logining...");
        ui->nameEdit->setEnabled(false);
        ui->passwdEdit->setEnabled(false);
        ui->checkBox->setEnabled(false);
        ui->checkBox_2->setEnabled(false);
        loginStatus=true;
        bool rememberStatus=ui->checkBox->isChecked();
        bool autoStatus=ui->checkBox_2->isChecked();
        auto cfg=configureReader.getCfg();
        configureReader.setCfg("remember",rememberStatus?"true":"false");
        configureReader.setCfg("auto",autoStatus?"true":"false");
        if(rememberStatus){
            configureReader.setCfg("name",name.toStdString());
            configureReader.setCfg("passwd",password.toStdString());
        }else{
            configureReader.setCfg("name","");
            configureReader.setCfg("passwd","");
        }
        configureReader.fresh();

        if(loginThread.get()!=nullptr)loginThread->wait();
        loginThread.reset(new LoginThread());
        loginThread->start();
        while(loginThread->getStatus()=="wait"){
            QEventLoop loop;
            QTimer::singleShot(1000,&loop,SLOT(quit()));
            loop.exec();
        }
        if(loginThread->getStatus()!="success"){
            QMessageBox::information(this,"Error",
                                     loginThread->getStatus(),
                                     QMessageBox::Ok);
            ui->loginButton->setText("login");
            on_loginButton_clicked();
            return;
        }
        ui->loginButton->setText("logout");
        if(cfg["automin"]=="true"){
            on_minButton_clicked();
        }
    }
}

void MainWindow::on_minButton_clicked()
{
    this->hide();
    auto cfg=configureReader.getCfg();
    if(cfg["tray"]=="false")return;
    systemTrayIcon.reset(new QSystemTrayIcon());
    QIcon qIcon=QIcon(":/png");
    systemTrayIcon->setToolTip("drcom-client");
    systemTrayIcon->setIcon(qIcon);
    connect(systemTrayIcon.get(),SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(onActivitedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    trayActionExit.reset(new QAction("Exit",this));
    trayActionShow.reset(new QAction("Show Main",this));
    connect(trayActionExit.get(),SIGNAL(triggered()),this,SLOT(exitAction()));
    connect(trayActionShow.get(),SIGNAL(triggered()),this,SLOT(showMainAction()));
    trayMenu.reset(new QMenu(this));
    trayMenu->addAction(trayActionShow.get());
    trayMenu->addAction(trayActionExit.get());
    systemTrayIcon->setContextMenu(trayMenu.get());
    systemTrayIcon->show();
}


void MainWindow::on_actionExit_triggered()
{
    if(loginThread.get()!=nullptr){
        loginThread->setExitFlagTrue();
        loginThread->wait();
    }
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

void MainWindow::onActivitedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        this->show();
        systemTrayIcon->hide();
        break;
    case QSystemTrayIcon::DoubleClick:
        systemTrayIcon->hide();
        break;
    default:
        break;
    }
}

void MainWindow::showMainAction()
{
    this->show();
    systemTrayIcon->hide();
}

void MainWindow::exitAction()
{
    if(loginThread.get()!=nullptr){
        loginThread->setExitFlagTrue();
        loginThread->wait();
    }
    exit(0);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(Qt::Unchecked==arg1){
        if(ui->checkBox_2->isChecked()){
            ui->checkBox_2->setChecked(false);
        }
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(Qt::Checked==arg1){
        if(!ui->checkBox->isChecked()){
            ui->checkBox->setChecked(true);
        }
    }
}

void MainWindow::on_actionSettings_triggered()
{
    settingsWindow.reset(new SettingsWindow(this));
    settingsWindow->show();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWindow.reset(new AboutWindow(this));
    aboutWindow->show();
}

void MainWindow::on_actionCheck_Log_triggered()
{
    logWindow.reset(new LogWindow(this));
    logWindow->show();
    logWindow->init();
}
