#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

#include "drcom.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool event(QEvent *e) override;

private slots:
    void on_loginButton_clicked();

    void on_minButton_clicked();

    void on_actionExit_triggered();

    void on_actionLogin_Logout_triggered();

    void on_actionMinimize_triggered();

    void on_rememberCheckBox_stateChanged(int state);

    void on_autoCheckBox_stateChanged(int state);

    void on_actionSettings_triggered();

    void on_actionAbout_triggered();

    void on_actionCheck_Log_triggered();

    void on_loginSuccess();

    void on_loginFailed(const QString &msg);

private:
    Ui::MainWindow *ui;
    bool loginned = false;
    Drcom drcom;
};

#endif // MAINWINDOW_H
