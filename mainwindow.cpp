#include "mainwindow.h"
#include <QPainter>
#include <chrono>
#include <cstdlib>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "HERE! ";
    qDebug() << players[0].animation_.cur_frame_ - players[0].animation_.frames_.begin();
    qDebug() << ControlVec.begin() - players[0].animation_.frames_.begin() << ControlVec.begin() - players[0].animation_.cur_frame_;

    startTimer(9);
}

void MainWindow::timerEvent(QTimerEvent *) {
    //players[0].animation_.cur_frame_ = players[0].animation_.frames_.begin();
    //players[1].animation_.cur_frame_ = players[1].animation_.frames_.begin();

    qDebug() << players[0].animation_.cur_frame_ - players[0].animation_.frames_.begin();
    for (Person& player : players) {
        player.ProcessKeyboard();
        qDebug() << "Updating animation";
        player.UpdateAnimation();
        qDebug() << "Updated animation";
        player.current_platform = player.HitsGround(ground);
        player.ApplyPhysics();
    }

    for (FreePig& pig : free_pigs) {
        pig.current_platform = pig.HitsGround(ground);
        pig.ApplyPhysics();
        pig.UpdatePosition();
    }

    for (int i = 0; i < flying_pigs.size(); i++) {
        if (!flying_pigs[i].if_Hits(players, ground)) {
            flying_pigs[i].UpdatePosition();
            if ((flying_pigs[i].position_.x > 1000) || (flying_pigs[i].position_.x < 0)) {
                flying_pigs.erase(flying_pigs.begin() + i);
            }
        } else {
            qDebug() << flying_pigs[i].if_Hits(players, ground);
            flying_pigs.erase(flying_pigs.begin() + i);
        }
    }
    repaint();
    for (Person& player : players) {
        player.UpdatePosition();
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    for (Person& player : players) {
        qDebug() << "Drawing person";
        player.Draw(p);
        qDebug() << "Drew person";
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
        if (player.current_side == MovingObject::Side::LEFT){
            ShotPig pig(player.position_.x - kPigSize,
                        player.position_.y - kPigSize, -1, &player);
            flying_pigs.push_back(pig);
        } else {
            ShotPig pig(player.position_.x + kPigSize,
                        player.position_.y - kPigSize, 1, &player);
            flying_pigs.push_back(pig);
        }
        player.armed_ = 0;
        free_pigs.push_back(GeneratePig());
    } else {
        if (!free_pigs.empty()) {
            auto piggo = player.FindClosestFreePig(*this);
            player.CatchPig(*piggo);
            free_pigs.erase(piggo);
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
    FreePig new_pig(10, 10);
    new_pig.setX(rand() % geometry().width());
    new_pig.setY(rand() % geometry().height());
    return new_pig;
}

MainWindow::~MainWindow()
{

}
