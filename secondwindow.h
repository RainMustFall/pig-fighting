#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(MainWindow *parent = nullptr);
    ~SecondWindow();

    MainWindow *parent;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
