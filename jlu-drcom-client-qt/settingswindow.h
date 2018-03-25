#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
