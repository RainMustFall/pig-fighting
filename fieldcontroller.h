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

class MainWindow;

class FieldController
{
public:
    FieldController(MainWindow* view, TextureType type = TextureType::GRASS);

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
    void PlayerWins(int name);

private:
    FreePig GeneratePig();
    Person* GetHitPerson(const GameObject* object);

    int cur_time_ = 0;
    bool is_start_ = true;

    std::vector<Person> players;
    std::vector<Ground>ground;
    std::list<HealthField> health_fields;
    std::vector<FreePig> free_pigs;
    std::list<ShotPig> flying_pigs;

    MainWindow* field_view_;
    PigAnimationStorage pig_animations_;
};

#endif // FIELDCONTROLLER_H
