#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "constants.h"
#include "person.h"
#include "ground.h"
#include "shotpig.h"
#include "soundplayer.h"
#include "health_field.h"
#include "fieldcontroller.h"

class TheMostMainWindow;

class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void timerEvent(QTimerEvent*) override;
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  void ThrowPig(Person& player);
  void NewGame(TextureType type);
  void DrawBackground();
  void DrawHint(QPainter& painter);
  void Pause(const QString& reason);
  void SetTimer();
  void StopTimer();
  void GameOver(int player);

  template<typename T>
  void drawPlayingObject(QPainter& p, const T& objects) {
      for (const auto& object: objects) {
          object.Draw(p);
      }
  }

  FreePig GeneratePig();

 private:

  QSoundEffect pig_caught;
  int timer_id;

  bool isTimerActive = true;
  bool is_start = true;
  bool paused = true;

  FieldController* controller_;
  TheMostMainWindow* parent_;
  TextureType cur_theme;

  const std::vector<QString> bg_dirs_ = {
      "grass",
      "sand",
      "cave",
      "snow"
  };
};

#endif // MAINWINDOW_H
