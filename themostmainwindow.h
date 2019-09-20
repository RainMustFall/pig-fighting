#ifndef THEMOSTMAINWINDOW_H
#define THEMOSTMAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class TheMostMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    TheMostMainWindow(QWidget *parent = nullptr);

    Ui::MainWindow* ui;
    MainWindow* win;
private slots:
    void on_new_game_clicked();
    void on_pause_clicked();
    void on_exit_clicked();
};

#endif // THEMOSTMAINWINDOW_H
