#include "fieldcontroller.h"
#include "constants.h"
#include "shotpig.h"
#include "mainwindow.h"

FieldController::FieldController()
{

}

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
    }
}

void FieldController::AddPigs() {
    if (free_pigs.empty()) {
        free_pigs.insert(free_pigs.end(), GeneratePig());
    } else if (rand() % kPigGeneraingFrequency == 0 && free_pigs.size() < kPigCount) {
        free_pigs.insert(free_pigs.end(), GeneratePig());
    }
}

void FieldController::UpdateFreePigs() {
    for (FreePig& pig : free_pigs) {
        pig.PositionGenerate();
        pig.current_platform = pig.HitsGround(ground);
        pig.ApplyPhysics();
        pig.UpdatePosition();
        pig.CheckBoundaries();
    }
}

void FieldController::UpdateFlyingPigs() {
    for (auto item = flying_pigs.begin(); item != flying_pigs.end(); ++item) {
        const GameObject* hitting_object = item->Pig_Hits(players, ground);
        if (hitting_object == nullptr) {
            item->UpdatePosition();
            if ((item->position_.x > kScreenWidth) || (item->position_.x < -item->Width())) {
                item = flying_pigs.erase(item);
            }
        } else if (dynamic_cast<const Person*>(hitting_object) != nullptr){
            QSound::play(":/resources/sounds/hit.mp3");
            players[0].PlayMusicHit();
            players[1].PlayMusicHit();
            item = flying_pigs.erase(item);
            const Person* hitting_person_const = dynamic_cast<const Person*>(hitting_object);
            Person* hitting_person = const_cast<Person*>(hitting_person_const);
            hitting_person->DecreaseHealthLevel();
            if (hitting_person->health_level <= 0) {
                // paused = true;
                if (hitting_person->name_ == 1) {
                    Pause("Игрок 2 выиграл!");
                } else {
                    Pause("Игрок 1 выиграл!");
                }
                killTimer(timer_id);
                is_start = true;

            }


        } else {
            QSound::play(":/resources/sounds/hit2.mp3");
            item->PlayMusic();
            item = flying_pigs.erase(item);
        }
    }
}

void FieldController::onPaintingStarted(QPainter& p) {
    field_view_->drawPlayingObjects(p, PackObjects());
    if (is_start_) {
        field_view_->DrawHint(p);
    } else if (cur_time_ == 2000){
       field_view_->DrawBackground();
    }
}

ObjectSet FieldController::PackObjects() {
    return {players, free_pigs, flying_pigs, health_fields, ground};
}

void FieldController::ThrowPig(Person& player) {
    if (player.armed_) {

        if (player.current_side == MovingObject::Side::LEFT){
            ShotPig pig(player.position_.x - kPigSize - 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, -1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
             pig.PlayMusicFly();
        } else {
            ShotPig pig(player.position_.x + player.Width() + 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, 1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
             //pig.PlayMusicFly();
        }
        player.armed_ = 0;

        free_pigs.push_back(GeneratePig());
    } else {
        std::list<FreePig>::iterator current_pig = player.HitsPig(free_pigs);
        qDebug() << current_pig->xPos() << ' ' << current_pig->yPos();
        if (current_pig != free_pigs.end()) {
            SoundPlayer* s_player = new SoundPlayer(SoundPlayer::Sounds::Hit, new QSound(":/resources/sounds/pig_caught.wav"));
            s_player->start();

            //QSound::play(":/resources/sounds/hit.wav");
            //pig_caught.play();

            player.CatchPig(*current_pig);
            //player.PlayMusic();
            free_pigs.erase(current_pig);
        }
    }
}

void FieldController::onKeyPressed(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Space:
        ThrowPig(players[0]);
        break;
    case Qt::Key_Shift:
        ThrowPig(players[1]);
        break;
    case Qt::Key_Escape: {

        field_view_->killTimer(field_view_->timer_id);
        field_view_->Pause("Пауза");
    }
        break;
    default:
        // Нажатия клавиш для обоих игроков (передаём в качестве аргумента нажатую клавишу
        // и четыре клавиши, отвечающие у этого игрока за верх, лево, низ, право)
        players[0].CatchPressedKey(event->key(), Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D);
        players[1].CatchPressedKey(event->key(), Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right);
    }
}

void FieldController::onKeyReleased(QKeyEvent *event) {
    players[0].CatchReleasedKey(event->key(), Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D);
    players[1].CatchReleasedKey(event->key(), Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right);
}

void FieldController::UpdateTimer() {
    ++cur_time_;
    if (cur_time_ > 200) {
        is_start_ = false;
    }
}

FreePig FieldController::GeneratePig() {
    FreePig new_pig(10, 10, &pig_running_l, &pig_running_r);
    new_pig.setX(rand() % field_view_->geometry().width());
    new_pig.setY(rand() % field_view_->geometry().height());
    return new_pig;
}
