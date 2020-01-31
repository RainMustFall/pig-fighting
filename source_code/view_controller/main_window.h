#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

#include "source_code/game_objects/person.h"
#include "./ui_mainwindow.h"
#include "./field_view.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  void Pause(bool game_over);

 private:
  bool paused_;
  Ui::MainWindow* ui_;
  FieldView* field_view_;

 public slots:  // NOLINT
  void GameOver(int player);

 private slots:  // NOLINT
  void on_new_game_clicked();
  void on_pause_clicked();
  void on_exit_clicked();
};

#endif  // MAIN_WINDOW_H_
