#include "main_window.h"
#include "field_view.h"
#include "person.h"
#include "constants.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      paused_(true),
      ui_(new Ui::MainWindow),
        field_view_(new FieldView(this))
{
    setWindowIcon(QIcon(kIconPath));
    setWindowTitle("Pig Fighting");

    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(field_view_);
    ui_->comboBox->addItem("Классический");
    ui_->comboBox->addItem("Песчаный");
    ui_->comboBox->addItem("Пещера");
    ui_->comboBox->addItem("Снежная");
}

void MainWindow::Pause(bool game_over) {
    if (!paused_) {
        ui_->new_game->setEnabled(true);
        ui_->comboBox->setEnabled(true);
        ui_->pause->setText("Продолжить");
        if (!game_over) {
            ui_->label_2->setText("Пауза");
        }
        field_view_->StopTimer();
    } else {
        field_view_->setFocus();
        ui_->new_game->setEnabled(false);
        ui_->comboBox->setEnabled(false);
        ui_->pause->setText("Пауза");
        ui_->label_2->setText("");
        field_view_->SetTimer();
    }

    if(game_over){
        ui_->pause->setEnabled(false);
    }

    paused_ = !paused_;
}

void MainWindow::GameOver(int player) {
    Pause(true);
    if (player == 1) {
        ui_->label_2->setText("Игрок 2 выиграл!");
    } else {
        ui_->label_2->setText("Игрок 1 выиграл!");
    }
}

void MainWindow::on_new_game_clicked()
{
    field_view_->NewGame(static_cast<utils::TextureType>(ui_->comboBox->currentIndex()));
    ui_->new_game->setEnabled(false);
    ui_->comboBox->setEnabled(false);
    ui_->pause->setEnabled(true);
    ui_->pause->setText("Пауза");
    ui_->label_2->setText("");
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
