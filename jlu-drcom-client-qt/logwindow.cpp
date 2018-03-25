#include "logwindow.h"
#include "ui_logwindow.h"
#include "loginthread.h"

LogWindow::LogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
}

void LogWindow::init()
{
    for(auto log:LoginThread::logs){
        ui->textBrowser->append(log);
    }
}

LogWindow::~LogWindow()
{
    delete ui;
}

void LogWindow::on_freshButton_clicked()
{
    ui->textBrowser->clear();
    for(auto log:LoginThread::logs){
        ui->textBrowser->append(log);
    }
}

void LogWindow::on_closeButton_clicked()
{
    this->hide();
}
