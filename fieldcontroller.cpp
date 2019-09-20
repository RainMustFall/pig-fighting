#include "fieldcontroller.h"
#include "constants.h"
#include "shotpig.h"
#include "mainwindow.h"

FieldController::FieldController()
    : pig_running_l(":/resources/animations/pig_running.png", 400, 400, kPigSize, kPigSize),
      pig_running_r(pig_running_l.returnReflectedCopy()),
      pig_flying_l(":/resources/animations/pig_flying.png", 400, 400, kPigSize, kPigSize),
      pig_flying_r(pig_flying_l.returnReflectedCopy()) {}

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
        pig.UpdatePlatform(ground);
        pig.ApplyPhysics();
        pig.UpdatePosition();
    }

    pig_running_l.NextFrame();
    pig_running_r.NextFrame();
}

void FieldController::UpdateFlyingPigs() {
    for (auto item = flying_pigs.begin(); item != flying_pigs.end(); ++item) {
        auto hitting_object = item->Pig_Hits(players, ground);
        if (hitting_object == nullptr) {
            item->UpdatePosition();
            if (item->isOutOfScreen()) {
                item = flying_pigs.erase(item);
            }
        } else if (GetHitPerson(hitting_object) != nullptr){
            item = flying_pigs.erase(item);
            auto hitting_person = GetHitPerson(hitting_object);
            hitting_person->DecreaseHealthLevel();
        } else {
            // PLAY hit2.wav!
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

void FieldController::onPigThrown(const ShotPig& pig) {
    flying_pigs.push_back(pig);
    free_pigs.push_back(GeneratePig());
    // PlaySound!
}

void FieldController::onPigCaught() {
    // PlaySound!
    // SoundPlayer* s_player = new SoundPlayer(SoundPlayer::Sounds::Hit, new QSound(":/resources/sounds/pig_caught.wav"));
    // s_player->start();
}

void FieldController::givePigsToPlayer(Person* player) {
    player->CatchPig(free_pigs);
}

void FieldController::onKeyPressed(QKeyEvent *event) {
    switch (event->key()) {
    /*case Qt::Key_Space:
        ThrowPig(players[0]);
        break;
    case Qt::Key_Shift:
        ThrowPig(players[1]);
        break;*/
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

Person* FieldController::GetHitPerson(const GameObject* object) {
    auto hitting_person_const = dynamic_cast<const Person*>(object);
    auto hitting_person = const_cast<Person*>(hitting_person_const);
    return hitting_person;
}
