#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>

namespace Ui
{
    class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGSWINDOW_H
