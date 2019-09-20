#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include "person.h"
#include <list>
#include "freepig.h"
#include "animation.h"
#include "health_field.h"
#include "shotpig.h"
#include "constants.h"

struct ObjectSet {
  const std::vector<Person>& players;
  const std::list<FreePig>& free_pigs;
  const std::list<ShotPig>& flying_pigs;
  const std::list<HealthField>& health_fields;
  const std::vector<Ground>& ground;
};

class MainWindow;

class FieldController
{
public:
    FieldController();

    void UpdatePlayers();
    void AddPigs();
    void UpdateFreePigs();
    void UpdateFlyingPigs();
    void onPaintingStarted(QPainter& p);
    void ThrowPig(Person& player);
    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void UpdateTimer();
    void onPigThrown(const ShotPig& pig);
    void onPigCaught();
    void givePigsToPlayer(Person* player);

private:
    std::vector<Person> players = {{450, 120, "player_1"},
                                   {800, 200, "player_2"}};

    std::list<FreePig> free_pigs;

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

    Animation pig_running_l;
    Animation pig_running_r;
    Animation pig_flying_l;
    Animation pig_flying_r;

    int cur_time_ = 0;
    bool is_start_ = true;
    ObjectSet PackObjects();
    FreePig GeneratePig();
    Person* GetHitPerson(const GameObject* object);
};

#endif // FIELDCONTROLLER_H
