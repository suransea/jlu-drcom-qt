#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>

namespace Ui
{
    class LogDialog;
}

class LogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogDialog(QWidget *parent = 0);
    ~LogDialog();

private slots:
    void on_freshButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::LogDialog *ui;
};

#endif // LOGWINDOW_H
