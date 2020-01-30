#ifndef PERSON_H
#define PERSON_H
#include "game_object.h"
#include "animation.h"
#include "moving_object.h"
#include "resource_storage.h"
#include "free_pig.h"
#include "utils.h"
#include <QMediaPlayer>
#include "constants.h"
#include <QMediaPlaylist>

class FieldController;

class Person: public MovingObject
{
public:
    Person(int x, int y, const QString& animation_dir, int id, FieldController* controller);

    void CatchPressedKey(int key);
    void CatchReleasedKey(int key);
    void ProcessKeyboard();
    void CatchPig(FreePig& pig);
    void UpdateAnimation();
    void Draw(QPainter& painter) const override;
    void ThrowPig();
    void CatchPig();
    void DecreaseHealthLevel();
    void IncreaseHelthLevel();

    int Health() const;

private:
    bool armed_ = 0;
    bool up_pressed_ = false;
    bool left_pressed_ = false;
    bool right_pressed_ = false;
    bool down_pressed_ = false;
    bool can_shoot_ = true;
    int health_level_ = 100;
    int name_;

    utils::PersonState state_;
    PersonAnimationStorage animations_;
    const utils::HandleKeys handle_keys_;
    FieldController* controller_;

    void ResetRunAnimation();
};

#endif // PERSON_H
