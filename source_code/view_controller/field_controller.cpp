#include "./field_controller.h"

#include <cstdlib>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>

#include "./main_window.h"
#include "source_code/utils/sound_player.h"
#include "./field_view.h"

FieldController::FieldController(FieldView* view, const QString& map_name,
                                 utils::TextureType type)
    : catch_sound_(new QSound(":/resources/sounds/pig_caught.wav")),
      throw_sound_(new QSound(":/resources/sounds/pig_caught.wav")),
      hit_sound_(new QSound(":/resources/sounds/hit.wav")),
      field_view_(view) {
  QFile file;
  file.setFileName(map_name);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QJsonParseError jsonError{};
  QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &jsonError);

  QJsonObject root = document.object();

  InitGround(root.value("ground").toArray(), type);
  InitPlayers(root.value("players").toArray());

  health_fields_ = {{10, 10, &players_[0]},
                    {kScreenWidth - 110, 10, &players_[1]}};
}

void FieldController::InitGround(const QJsonArray& ground,
                                 utils::TextureType type) {
  for (int i = 0; i < ground.count(); i++) {
    QJsonObject platform = ground.at(i).toObject();
    ground_.emplace_back(platform.value("x").toInt(),
                         platform.value("y").toInt(),
                         platform.value("height").toInt(),
                         platform.value("width").toInt(), type);
  }
}

void FieldController::InitPlayers(const QJsonArray& players) {
  for (int i = 0; i < players.count(); i++) {
    QJsonObject player = players.at(i).toObject();
    players_.emplace_back(player.value("x").toInt(), player.value("y").toInt(),
                          player.value("animation_dir").toString(),
                          player.value("id").toInt(), this);
  }
}

void FieldController::PlaySound(QSound *sound) {
    auto* s_player = new SoundPlayer(sound);
    connect(s_player, &SoundPlayer::finished, s_player, &QObject::deleteLater);
    s_player->start();
}

void FieldController::UpdatePlayers() {
  for (Person& player : players_) {
    player.ProcessKeyboard();
    player.UpdateAnimation();
    player.UpdatePlatform(ground_);
    player.ApplyPhysics();

    if (cur_time_ == kTimeHealthUp) {
      cur_time_ = 0;
      player.IncreaseHelthLevel();
    }

    player.UpdatePosition();
    player.CheckBoundaries();
  }
}

void FieldController::AddPigs() {
  if (free_pigs_.empty()) {
    free_pigs_.insert(free_pigs_.end(), GeneratePig());
  } else if (rand() % kPigGeneraingFrequency == 0 &&
             free_pigs_.size() < kPigCount) {
    free_pigs_.insert(free_pigs_.end(), GeneratePig());
  }
}

void FieldController::UpdateFreePigs() {
  for (FreePig& pig : free_pigs_) {
    pig.PositionGenerate();
    pig.UpdatePlatform(ground_);
    pig.ApplyPhysics();
    pig.UpdatePosition();
    pig.CheckBoundaries();
  }

  pig_animations_.run_l.NextFrame();
  pig_animations_.run_r.NextFrame();
}

void FieldController::UpdateFlyingPigs() {
  for (auto item = flying_pigs_.begin(); item != flying_pigs_.end(); ++item) {
    auto hitting_object = item->PigHits(&players_, &ground_);
    if (hitting_object == nullptr) {
      // if still flying
      item->UpdatePosition();
      if (item->IsOutOfScreen()) {
        item = flying_pigs_.erase(item);
      }
    } else if (dynamic_cast<Person*>(hitting_object) != nullptr) {
      // if hits a player
      item = flying_pigs_.erase(item);
      auto hitting_person = dynamic_cast<Person*>(hitting_object);
      hitting_person->DecreaseHealthLevel();
      PlaySound(hit_sound_);
    } else {
      // if hits another object
      item = flying_pigs_.erase(item);
    }
  }
}

void FieldController::OnPaintingStarted(QPainter* p) {
  field_view_->DrawPlayingObject(p, players_);
  field_view_->DrawPlayingObject(p, free_pigs_);
  field_view_->DrawPlayingObject(p, flying_pigs_);
  field_view_->DrawPlayingObject(p, health_fields_);
  field_view_->DrawPlayingObject(p, ground_);

  if (is_start_) {
    field_view_->DrawHint(p);
  } else if (cur_time_ == 2000) {
    field_view_->DrawBackground();
  }
}

void FieldController::OnPigThrown(int x, int y, int direction,
                                  const Person* sender) {
  flying_pigs_.emplace_back(x, y, direction, sender, &pig_animations_);
  free_pigs_.push_back(GeneratePig());
  PlaySound(throw_sound_);
}

void FieldController::GivePigsToPlayer(Person* player) {
  for (auto pig = free_pigs_.begin(); pig != free_pigs_.end(); ++pig) {
    auto item_obj = dynamic_cast<const GameObject*>(&*pig);

    if (player->Hits(item_obj)) {
      free_pigs_.erase(pig);
      player->CatchPig();
      PlaySound(catch_sound_);
      break;
    }
  }
}

void FieldController::OnKeyPressed(QKeyEvent* event) {
  for (auto& player : players_) {
    player.CatchPressedKey(event->key());
  }
}

void FieldController::OnKeyReleased(QKeyEvent* event) {
  for (auto& player : players_) {
    player.CatchReleasedKey(event->key());
  }
}

void FieldController::UpdateTimer() {
  ++cur_time_;
  if (cur_time_ > 200) {
    is_start_ = false;
  }
}

FreePig FieldController::GeneratePig() {
  FreePig new_pig(0, 0, &pig_animations_);
  new_pig.SetX(rand() % field_view_->geometry().width());
  new_pig.SetY(rand() % field_view_->geometry().height());
  return new_pig;
}

void FieldController::DeletePlayer(SoundPlayer* s_player)
{
    delete s_player;
    qDebug() << "Deleted!";
}

void FieldController::PlayerWins(int player) { field_view_->GameOver(player); }
