#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>

namespace Ui {
class LogWindow;
}

class LogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = 0);
    void init();
    ~LogWindow();

private slots:
    void on_freshButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::LogWindow *ui;
};

#endif // LOGWINDOW_H
