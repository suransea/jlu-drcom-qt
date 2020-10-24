#include "logdialog.h"
#include "ui_logdialog.h"

#include "drcom.h"
#include "log.h"

LogDialog::LogDialog(QWidget *parent) : QDialog(parent),
                                        ui(new Ui::LogDialog)
{
    ui->setupUi(this);
    for (auto &&log : Log::history)
    {
        ui->textBrowser->append(log);
    }
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::on_freshButton_clicked()
{
    ui->textBrowser->clear();
    for (auto &&log : Log::history)
    {
        ui->textBrowser->append(log);
    }
}

void LogDialog::on_closeButton_clicked()
{
    this->close();
}
