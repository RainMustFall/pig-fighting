#include "./main_window.h"

#include <QDebug>

#include "./field_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      paused_(true),
      ui_(new Ui::MainWindow),
      field_view_(new FieldView(this)) {
  setWindowIcon(QIcon(kIconPath));
  setWindowTitle("Pig Fighting");

  ui_->setupUi(this);
  ui_->verticalLayout->addWidget(field_view_);

  ui_->background_box->addItem("Classical");
  ui_->background_box->addItem("Sandy");
  ui_->background_box->addItem("Cave");
  ui_->background_box->addItem("Snowy");

  ui_->map_box->addItem("Map 1");
}

void MainWindow::Pause(bool game_over) {
  if (!paused_) {
    ui_->new_game->setEnabled(true);
    ui_->background_box->setEnabled(true);
    ui_->pause->setText("Continue");
    if (!game_over) {
      ui_->state_label->setText("Pause");
    }
    field_view_->StopTimer();
  } else {
    field_view_->setFocus();
    ui_->new_game->setEnabled(false);
    ui_->background_box->setEnabled(false);
    ui_->pause->setText("Pause");
    ui_->state_label->setText("");
    field_view_->SetTimer();
  }

  if (game_over) {
    ui_->pause->setEnabled(false);
  }

  paused_ = !paused_;
}

void MainWindow::GameOver(int player) {
  Pause(true);
  if (player == 1) {
    ui_->state_label->setText("Player 2 won!");
  } else {
    ui_->state_label->setText("Player 1 won!");
  }
}

void MainWindow::on_new_game_clicked() {
  field_view_->NewGame(
      static_cast<utils::TextureType>(ui_->background_box->currentIndex()),
      ui_->map_box->currentText());
  ui_->new_game->setEnabled(false);
  ui_->background_box->setEnabled(false);
  ui_->pause->setEnabled(true);
  ui_->pause->setText("Pause");
  ui_->state_label->setText("");
  paused_ = false;
}

void MainWindow::on_pause_clicked() { Pause(false); }

void MainWindow::on_exit_clicked() { QApplication::exit(0); }

MainWindow::~MainWindow() {
  delete ui_;
  delete field_view_;
}
