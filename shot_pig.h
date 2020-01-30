#ifndef SHOT_PIG_H_
#define SHOT_PIG_H_

#include <vector>

#include "./moving_object.h"
#include "./game_object.h"
#include "./person.h"
#include "./resource_storage.h"

class ShotPig : public MovingObject {
 public:
  ShotPig(int x, int y, int direction, const Person* shooting_player_,
          const PigAnimationStorage* animations);

  GameObject* PigHits(std::vector<Person>* persons,
                             std::vector<Ground>* ground);

  void Draw(QPainter* painter) const override;
  bool IsOutOfScreen();

 private:
  const Person* shooting_player_;
  const PigAnimationStorage* animations_;
};

#endif  // SHOT_PIG_H_
