#ifndef THEMOSTMAINWINDOW_H
#define THEMOSTMAINWINDOW_H

#include <QMainWindow>
#include "person.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

class TheMostMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    TheMostMainWindow(QWidget *parent = nullptr);
    void Pause(bool game_over);

private:
    bool paused_;
    Ui::MainWindow* ui;
    MainWindow* win;

public slots:
    void GameOver(int player);

private slots:
    void on_new_game_clicked();
    void on_pause_clicked();
    void on_exit_clicked();
};

#endif // THEMOSTMAINWINDOW_H
