#include "mainwindow.h"
#include "constants.h"
#include "health_field.h"
#include <QPainter>
#include <chrono>
#include <cstdlib>
#include <QMouseEvent>
#include <QDebug>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    pig_running_l(":/resources/animations/pig_running.png", 400, 400, kPigSize, kPigSize),
    pig_running_r(Reflect(pig_running_l)),
    pig_flying_l(":/resources/animations/pig_flying.png", 400, 400, kPigSize, kPigSize),
    pig_flying_r(Reflect(pig_flying_l))
{

    qDebug() << "HERE! ";
    pig_caught.setSource(QUrl::fromLocalFile(":/resources/sounds/pig_caught.mp3"));
    pig_caught.setVolume(0.25f);

    startTimer(9);
}

void MainWindow::timerEvent(QTimerEvent *) {
    setFocus();
    time++;
    for (Person& player : players) {
        player.ProcessKeyboard();
        player.UpdateAnimation();
        player.current_platform = player.HitsGround(ground);
        player.ApplyPhysics();
        if (time == kTimeHealthUp) {
            time = 0;
            player.IncreaseHelthLevel();
        }
    }

    if (free_pigs.empty()) {
        free_pigs.insert(free_pigs.end(), GeneratePig());
    } else if (rand() % 500 == 0 && free_pigs.size() < kPigCount) {
        free_pigs.insert(free_pigs.end(), GeneratePig());
    }

    pig_running_l.NextFrame();
    pig_running_r.NextFrame();

    for (FreePig& pig : free_pigs) {
        pig.PositionGenerate();
        pig.current_platform = pig.HitsGround(ground);
        pig.ApplyPhysics();
    }

    for (auto item = flying_pigs.begin(); item != flying_pigs.end(); ++item) {
        const GameObject* hitting_object = item->Pig_Hits(players, ground);
        if (hitting_object == nullptr) {
            item->UpdatePosition();
            if ((item->position_.x > kScreenWidth) || (item->position_.x < -item->Width())) {
                item = flying_pigs.erase(item);
            }
        } else if (dynamic_cast<const Person*>(hitting_object) != nullptr){
            QSound::play(":/resources/sounds/hit.mp3");
            item = flying_pigs.erase(item);
            const Person* hitting_person_const = dynamic_cast<const Person*>(hitting_object);
            Person* hitting_person = const_cast<Person*>(hitting_person_const);
            hitting_person->DecreaseHealthLevel();

        } else {
            QSound::play(":/resources/sounds/hit2.mp3");
            item = flying_pigs.erase(item);
        }
    }

    repaint();
    for (Person& player : players) {
        player.UpdatePosition();
        player.CheckBoundaries();
    }
    for (FreePig& pig : free_pigs) {
        pig.UpdatePosition();
        pig.CheckBoundaries();
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    for (Person& player : players) {
        player.Draw(p);
    }
    for (HealthField& field : health_fields) {
        field.Draw(p);
    }
    for (auto& item:ground) {
        item.Draw(p);
    }
    for (FreePig& item: free_pigs) {
        item.Draw(p);
    }
    for (ShotPig& item: flying_pigs) {
        item.Draw(p);
    }
    p.end();
}

void MainWindow::ThrowPig(Person& player) {
    if (player.armed_) {
        QSound::play(":/resources/sounds/pig_fly.mp3");
        if (player.current_side == MovingObject::Side::LEFT){
            ShotPig pig(player.position_.x - kPigSize - 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, -1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
        } else {
            ShotPig pig(player.position_.x + player.Width() + 1,
                        player.position_.y + player.Height() - kPigSize - kPigHeight, 1,
                        &player, &pig_flying_l, &pig_flying_r);
            flying_pigs.push_back(pig);
        }
        player.armed_ = 0;
        //free_pigs.push_back(GeneratePig());
    } else {
        std::list<FreePig>::iterator current_pig = player.HitsPig(free_pigs);
        qDebug() << current_pig->xPos() << ' ' << current_pig->yPos();
        if (current_pig != free_pigs.end()) {
//            QSound::play(":/resources/sounds/pig_caught.mp3");
            pig_caught.play();
            player.CatchPig(*current_pig);
            free_pigs.erase(current_pig);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Space:
        ThrowPig(players[0]);
        break;
    case Qt::Key_Shift:
        ThrowPig(players[1]);
        break;
    default:
        // Нажатия клавиш для обоих игроков (передаём в качестве аргумента нажатую клавишу
        // и четыре клавиши, отвечающие у этого игрока за верх, лево, низ, право)
        players[0].CatchPressedKey(event->key(), Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D);
        players[1].CatchPressedKey(event->key(), Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    players[0].CatchReleasedKey(event->key(), Qt::Key_W, Qt::Key_A, Qt::Key_S, Qt::Key_D);
    players[1].CatchReleasedKey(event->key(), Qt::Key_Up, Qt::Key_Left, Qt::Key_Down, Qt::Key_Right);
}

FreePig MainWindow::GeneratePig() {
    FreePig new_pig(10, 10, &pig_running_l, &pig_running_r);
    new_pig.setX(rand() % geometry().width());
    new_pig.setY(rand() % geometry().height());
    return new_pig;
}

MainWindow::~MainWindow()
{

}
