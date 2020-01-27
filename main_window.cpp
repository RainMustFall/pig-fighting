#include "main_window.h"
#include "field_view.h"
#include "person.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      paused_(true),
      ui(new Ui::MainWindow),
        win(new FieldView(this))
{
    setWindowIcon(QIcon(":/resources/textures/icon.ico"));
    setWindowTitle("Pig Fighting");

    ui->setupUi(this);
    ui->verticalLayout->addWidget(win);
    ui->comboBox->addItem("Классический");
    ui->comboBox->addItem("Песчаный");
    ui->comboBox->addItem("Пещера");
    ui->comboBox->addItem("Снежная");
}

void MainWindow::Pause(bool game_over) {
    if (!paused_) {
        ui->new_game->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->pause->setText("Продолжить");
        if (!game_over) {
            ui->label_2->setText("Пауза");
        }
        win->StopTimer();
    } else {
        win->setFocus();
        ui->new_game->setEnabled(false);
        ui->comboBox->setEnabled(false);
        ui->pause->setText("Пауза");
        ui->label_2->setText("");
        win->SetTimer();
    }

    if(game_over){
        ui->pause->setEnabled(false);
    }

    paused_ = !paused_;
}

void MainWindow::GameOver(int player) {
    Pause(true);
    if (player == 1) {
        ui->label_2->setText("Игрок 2 выиграл!");
    } else {
        ui->label_2->setText("Игрок 1 выиграл!");
    }
}

void MainWindow::on_new_game_clicked()
{
    win->NewGame(static_cast<utils::TextureType>(ui->comboBox->currentIndex()));
    ui->new_game->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->pause->setEnabled(true);
    ui->pause->setText("Пауза");
    ui->label_2->setText("");
    paused_ = false;
}

void MainWindow::on_pause_clicked()
{
    Pause(false);
}

void MainWindow::on_exit_clicked()
{
    QApplication::exit(0);
}
