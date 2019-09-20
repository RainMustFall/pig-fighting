#ifndef PERSON_H
#define PERSON_H
#include "gameobject.h"
#include "animation.h"
#include "movingobject.h"
#include "freepig.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

class FieldController;

class Person: public MovingObject
{
public:

    Person(int x, int y, QString animation_dir);

    void CatchPressedKey(int key, const int up_key, const int left_key,
                         const int down_key, const int right_key);
    void CatchReleasedKey(int key, const int up_key, const int left_key,
                         const int down_key, const int right_key);
    // Проверяет, какие клавиши нажаты,
    // и обрабатывает все нажатия
    void ProcessKeyboard();
    void CatchPig(FreePig& pig);
    void UpdateAnimation();
    void Draw(QPainter& painter) const override;
    void ThrowPig();
    void CatchPig(std::list<FreePig>& pigs);

    // std::list<FreePig>::iterator FindClosestFreePig(MainWindow& w);

    bool armed_ = 0;
    // Флаги, показывающие, какие клавиши зажаты
    // в текущий момент времени
    bool Up_pressed = false;
    bool Left_pressed = false;
    bool Right_pressed = false;
    bool Down_pressed = false;

    // Объекты, отвечающие за проигрывание анимации
    Animation run_animation_r;
    Animation stand_animation_r;
    Animation fly_animation_r;

    Animation run_animation_l;
    Animation stand_animation_l;
    Animation fly_animation_l;

    Animation run_animation_r_pig;
    Animation stand_animation_r_pig;
    Animation fly_animation_r_pig;

    Animation run_animation_l_pig;
    Animation stand_animation_l_pig;
    Animation fly_animation_l_pig;

    std::list<FreePig>::iterator HitsPig(std::list<FreePig>& pigs);

    int health_level = 100;

    void DecreaseHealthLevel();
    void IncreaseHelthLevel();
    void ResetRunAnimation();
    
    enum class State {
        RUNNING,
        STANDING,
        FLYING
    };

    State state;
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    QMediaPlayer *h_player;
    QMediaPlaylist *h_playlist;
    void PlayMusic();
    void PlayMusicHit();
    int name_;
    FieldController* controller_;

signals:
    void PlayerWins(int name);

protected:
    void UpdateAnimationUniversal(Animation& run_animation,
                                  Animation& stand_animation,
                                  Animation& fly_animation);

    void DrawUniversal(QPainter& painter,
                               const Animation& run_animation,
                               const Animation& stand_animation,
                               const Animation& fly_animation) const;
};

#endif // PERSON_H
