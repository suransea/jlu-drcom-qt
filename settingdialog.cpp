#include "settingdialog.h"
#include "ui_settingdialog.h"

#include "configmapper.h"

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent),
                                                ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    auto &&config = ConfigMapper::instance;
    ui->macEdit->setText(config["mac"]);
    ui->serverEdit->setText(config["server"]);
    ui->autoMinCheckBox->setChecked(config["automin"] == "true");
    ui->showTrayCheckBox->setChecked(config["tray"] == "true");
    if (config["server_changeable"] == "false")
    {
        ui->serverEdit->setEnabled(false);
    }
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->button(QDialogButtonBox::Save) == button)
    {
        auto &&config = ConfigMapper::instance;
        config.set("mac", ui->macEdit->text());
        config.set("server", ui->serverEdit->text());
        config.set("automin", ui->autoMinCheckBox->isChecked() ? "true" : "false");
        config.set("tray", ui->showTrayCheckBox->isChecked() ? "true" : "false");
        config.flush();
    }
}
