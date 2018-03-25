#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "mainwindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    auto cfg=MainWindow::configureReader.getCfg();
    ui->macEdit->setText(QString::fromStdString(cfg["mac"]));
    ui->serverEdit->setText(QString::fromStdString(cfg["server"]));
    ui->autoMinCheckBox->setChecked(cfg["automin"]=="true"?true:false);
    ui->showTrayCheckBox->setChecked(cfg["tray"]=="true"?true:false);
    if(cfg["server_changeable"]=="false"){
        ui->serverEdit->setEnabled(false);
    }
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Save)==button){
         auto cfg=MainWindow::configureReader.getCfg();
         MainWindow::configureReader.
                  setCfg("mac",ui->macEdit->text().toStdString());
         MainWindow::configureReader.
                  setCfg("server",ui->serverEdit->text().toStdString());
         MainWindow::configureReader.setCfg("automin",
                   ui->autoMinCheckBox->isChecked()?"true":"false");
         MainWindow::configureReader.setCfg("tray",
                   ui->showTrayCheckBox->isChecked()?"true":"false");
         MainWindow::configureReader.fresh();
    }
}
