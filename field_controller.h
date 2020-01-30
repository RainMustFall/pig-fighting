#ifndef FIELD_CONTROLLER_H_
#define FIELD_CONTROLLER_H_

#include <list>
#include <vector>

#include "./person.h"
#include "./free_pig.h"
#include "./animation.h"
#include "./health_field.h"
#include "./shot_pig.h"
#include "./constants.h"
#include "./resource_storage.h"

class FieldView;

class FieldController {
 public:
  FieldController(FieldView* view,
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
  FreePig GeneratePig();

  int cur_time_ = 0;
  bool is_start_ = true;

  std::vector<Person> players;
  std::vector<Ground> ground;
  std::list<HealthField> health_fields;
  std::vector<FreePig> free_pigs;
  std::list<ShotPig> flying_pigs;

  FieldView* field_view_;
  PigAnimationStorage pig_animations_;
};

#endif  // FIELD_CONTROLLER_H_
