#ifndef FIELD_VIEW_H_
#define FIELD_VIEW_H_

#include <QMainWindow>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <vector>

#include "./constants.h"
#include "./person.h"
#include "./ground.h"
#include "./shot_pig.h"
#include "./sound_player.h"
#include "./health_field.h"
#include "./field_controller.h"

class MainWindow;

class FieldView : public QMainWindow {
 public:
  explicit FieldView(QWidget* parent = nullptr);
  ~FieldView() override;

  void timerEvent(QTimerEvent*) override;
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  void ThrowPig(Person* player);
  void NewGame(utils::TextureType type);
  void DrawBackground();
  void DrawHint(QPainter* painter);
  void Pause(const QString* reason);
  void SetTimer();
  void StopTimer();
  void GameOver(int player);

  template <typename T>
  void DrawPlayingObject(QPainter* p, const T& objects) {
    for (const auto& object : objects) {
      object.Draw(p);
    }
  }

  FreePig GeneratePig();

 private:
  QSoundEffect pig_caught_;
  int timer_id_{};

  bool is_timer_active_ = true;
  bool is_start_ = true;
  bool paused_ = true;

  FieldController* controller_;
  MainWindow* parent_;
  utils::TextureType cur_theme_;

  const std::vector<QString> background_dirs_ = {
      "grass",
      "sand",
      "cave",
      "snow"
  };
};

#endif  // FIELD_VIEW_H_
