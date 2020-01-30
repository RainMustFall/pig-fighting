#ifndef THEMOSTMAINWINDOW_H
#define THEMOSTMAINWINDOW_H

#include <QMainWindow>
#include "person.h"
#include "ui_mainwindow.h"
#include "field_view.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void Pause(bool game_over);

private:
    bool paused_;
    Ui::MainWindow* ui_;
    FieldView* field_view_;

public slots:
    void GameOver(int player);

private slots:
    void on_new_game_clicked();
    void on_pause_clicked();
    void on_exit_clicked();
};

#endif // THEMOSTMAINWINDOW_H
