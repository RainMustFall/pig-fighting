#ifndef FIELD_CONTROLLER_H_
#define FIELD_CONTROLLER_H_

#include <list>
#include <vector>
#include <queue>

#include "source_code/game_objects/person.h"
#include "source_code/game_objects/pig_classes/free_pig.h"
#include "source_code/game_objects//health_field.h"
#include "source_code/game_objects/pig_classes/shot_pig.h"
#include "source_code/utils/animation.h"
#include "source_code/utils/constants.h"
#include "source_code/utils/resource_storage.h"
#include "source_code/utils/sound_player.h"

class FieldView;

class FieldController : public QObject {
 public:
  FieldController(FieldView* view,
                  const QString& map_name,
                  utils::TextureType type = utils::TextureType::GRASS);

  void UpdatePlayers();
  void AddPigs();
  void UpdateFreePigs();
  void UpdateFlyingPigs();
  void OnPaintingStarted(QPainter* p);
  void ThrowPig(Person* player);
  void OnKeyPressed(QKeyEvent* event);
  void OnKeyReleased(QKeyEvent* event);
  void UpdateTimer();
  void OnPigThrown(int x, int y, int direction, const Person* sender);
  void GivePigsToPlayer(Person* player);
  void PlayerWins(int player);

 private:
  void InitGround(const QJsonArray& ground, utils::TextureType type);
  void InitPlayers(const QJsonArray& players);
  void PlaySound(QSound* sound);

  FreePig GeneratePig();

  int cur_time_ = 0;
  bool is_start_ = true;

  std::vector<Person> players_;
  std::vector<Ground> ground_;
  std::list<HealthField> health_fields_;
  std::vector<FreePig> free_pigs_;
  std::list<ShotPig> flying_pigs_;

  QSound* catch_sound_;
  QSound* throw_sound_;
  QSound* hit_sound_;

  FieldView* field_view_;
  PigAnimationStorage pig_animations_;

private slots:
  void DeletePlayer(SoundPlayer* s_player);
};

#endif  // FIELD_CONTROLLER_H_
