#include "./field_controller.h"

#include <stdlib.h>

#include "./main_window.h"
#include "./field_view.h"

FieldController::FieldController(FieldView* view, utils::TextureType type)
    : players{{450, 120, "player_1", 1, this}, {800, 200, "player_2", 2, this}},
      ground{{-146, 160, 30, 420, type}, {587, 130, 30, 270, type},
             {327, 327, 30, 270, type},  {935, 327, 30, 270, type},
             {1193, 160, 30, 270, type}, {1068, 486, 30, 270, type},
             {-52, 486, 30, 270, type},  {122, 656, 30, 1200, type}},
      health_fields{{10, 10, &players[0]},
                    {kScreenWidth - 110, 10, &players[1]}},
      field_view_(view) {}

void FieldController::UpdatePlayers() {
  for (Person& player : players) {
    player.ProcessKeyboard();
    player.UpdateAnimation();
    player.UpdatePlatform(ground);
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
  if (free_pigs.empty()) {
    free_pigs.insert(free_pigs.end(), GeneratePig());
  } else if (rand() % kPigGeneraingFrequency == 0 &&
             free_pigs.size() < kPigCount) {
    free_pigs.insert(free_pigs.end(), GeneratePig());
  }
}

void FieldController::UpdateFreePigs() {
  for (FreePig& pig : free_pigs) {
    pig.PositionGenerate();
    pig.UpdatePlatform(ground);
    pig.ApplyPhysics();
    pig.UpdatePosition();
    pig.CheckBoundaries();
  }

  pig_animations_.run_l.NextFrame();
  pig_animations_.run_r.NextFrame();
}

void FieldController::UpdateFlyingPigs() {
  for (auto item = flying_pigs.begin(); item != flying_pigs.end(); ++item) {
    auto hitting_object = item->PigHits(&players, &ground);
    if (hitting_object == nullptr) {
      // if still flying
      item->UpdatePosition();
      if (item->IsOutOfScreen()) {
        item = flying_pigs.erase(item);
      }
    } else if (dynamic_cast<Person*>(hitting_object) != nullptr) {
      // if hits a player
      item = flying_pigs.erase(item);
      auto hitting_person = dynamic_cast<Person*>(hitting_object);
      hitting_person->DecreaseHealthLevel();
      auto* s_player = new SoundPlayer(utils::Sounds::Hit);
      s_player->start();
    } else {
      // if hits another object
      item = flying_pigs.erase(item);
    }
  }
}

void FieldController::OnPaintingStarted(QPainter* p) {
  field_view_->DrawPlayingObject(p, players);
  field_view_->DrawPlayingObject(p, free_pigs);
  field_view_->DrawPlayingObject(p, flying_pigs);
  field_view_->DrawPlayingObject(p, health_fields);
  field_view_->DrawPlayingObject(p, ground);

  if (is_start_) {
    field_view_->DrawHint(p);
  } else if (cur_time_ == 2000) {
    field_view_->DrawBackground();
  }
}

void FieldController::OnPigThrown(int x, int y, int direction,
                                  const Person* sender) {
  flying_pigs.emplace_back(x, y, direction, sender, &pig_animations_);
  free_pigs.push_back(GeneratePig());
  auto* s_player = new SoundPlayer(utils::Sounds::Throw);
  s_player->start();
}

void FieldController::GivePigsToPlayer(Person* player) {
  for (auto pig = free_pigs.begin(); pig != free_pigs.end(); ++pig) {
    auto item_obj = dynamic_cast<const GameObject*>(&*pig);

    if (player->Hits(item_obj)) {
      free_pigs.erase(pig);
      player->CatchPig();
      auto* s_player = new SoundPlayer(utils::Sounds::Take);
      s_player->start();
      break;
    }
  }
}

void FieldController::OnKeyPressed(QKeyEvent* event) {
  for (auto& player : players) {
    player.CatchPressedKey(event->key());
  }
}

void FieldController::OnKeyReleased(QKeyEvent* event) {
  for (auto& player : players) {
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

void FieldController::PlayerWins(int player) { field_view_->GameOver(player); }
