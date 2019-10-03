#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include "person.h"
#include <list>
#include "freepig.h"
#include "animation.h"
#include "health_field.h"
#include "shotpig.h"
#include "constants.h"
#include "resourcestorage.h"

struct ObjectSet {
  const std::vector<Person>& players;
  const std::vector<FreePig>& free_pigs;
  const std::list<ShotPig>& flying_pigs;
  const std::list<HealthField>& health_fields;
  const std::vector<Ground>& ground;
};

class MainWindow;

class FieldController
{
public:
    FieldController(MainWindow* view);

    void UpdatePlayers();
    void AddPigs();
    void UpdateFreePigs();
    void UpdateFlyingPigs();
    void onPaintingStarted(QPainter& p);
    void ThrowPig(Person& player);
    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void UpdateTimer();
    void onPigThrown(int x, int y, int direction, const Person* sender);
    void givePigsToPlayer(Person* player);

private:
    std::vector<Person> players;

    std::vector<FreePig> free_pigs;

    std::list<ShotPig> flying_pigs = {};


    std::list<HealthField> health_fields = {
           {10,10,100, &players[0]},
           {kScreenWidth - 110,10,100, &players[1]}
       };

    std::vector<Ground>ground = {{-146, 160, 30, 420},
                                 {587, 130, 30, 270},
                                 {327, 327, 30, 270},
                                 {935, 327, 30, 270},
                                 {1193, 160, 30, 270},
                                 {1068, 486, 30, 270},
                                 {-52, 486, 30, 270},
                                 {122, 656, 30, 1200}};

    MainWindow* field_view_;

    int cur_time_ = 0;
    bool is_start_ = true;
    ObjectSet PackObjects();
    FreePig GeneratePig();
    Person* GetHitPerson(const GameObject* object);

    PigAnimationStorage pig_animations_;
};

#endif // FIELDCONTROLLER_H
