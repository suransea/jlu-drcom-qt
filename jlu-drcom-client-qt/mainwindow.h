#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loginthread.h"
#include "configurereader.h"
#include "settingswindow.h"
#include "aboutwindow.h"
#include "logwindow.h"
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <iostream>
#include <string>
#include <QAction>
#include <QMenu>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static ConfigureReader configureReader;
    void init();
    ~MainWindow();

private slots:
    void on_loginButton_clicked();

    void on_minButton_clicked();

    void on_actionExit_triggered();

    void on_actionLogin_Logout_triggered();

    void on_actionMinimize_triggered();

    void onActivitedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void showMainAction();

    void exitAction();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_actionSettings_triggered();

    void on_actionAbout_triggered();

    void on_actionCheck_Log_triggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QSystemTrayIcon> systemTrayIcon;
    std::unique_ptr<QMenu> trayMenu;
    std::unique_ptr<QAction> trayActionExit;
    std::unique_ptr<QAction> trayActionShow;
    std::unique_ptr<SettingsWindow> settingsWindow;
    std::unique_ptr<AboutWindow> aboutWindow;
    std::unique_ptr<LogWindow> logWindow;
    bool loginStatus=false;
    std::unique_ptr<LoginThread> loginThread;
};

#endif // MAINWINDOW_H
