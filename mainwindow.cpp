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

    startTimer(9);
}

void MainWindow::timerEvent(QTimerEvent *) {
    for (Person& player : players) {
        player.ProcessKeyboard();
        player.UpdateAnimation();
        player.current_platform = player.HitsGround(ground);
        player.ApplyPhysics();
    }

    for (FreePig& pig : free_pigs) {
        pig.PositionGenerate();
        pig.current_platform = pig.HitsGround(ground);
        pig.ApplyPhysics();
//        pig.UpdatePosition();
    }

    for (auto item = flying_pigs.begin(); item != flying_pigs.end(); ++item) {
        if (!item->if_Hits(players, ground)) {
            item->UpdatePosition();
            if ((item->position_.x > kScreenWidth) || (item->position_.x < -item->Width())) {
                item = flying_pigs.erase(item);
            }
        } else {
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
            ShotPig pig(player.position_.x - kPigSize - 1,
                        player.position_.y + player.Height() - kPigSize - 1, -1, &player);
            flying_pigs.push_back(pig);
        } else {
            ShotPig pig(player.position_.x + player.Width() + 1,
                        player.position_.y + player.Height() - kPigSize - 1, 1, &player);
            flying_pigs.push_back(pig);
        }
        player.armed_ = 0;
        free_pigs.push_back(GeneratePig());
    } else {
        std::list<FreePig>::iterator current_pig = player.HitsPig(free_pigs);
        qDebug() << current_pig->xPos() << ' ' << current_pig->yPos();
        if (current_pig != free_pigs.end()) {
            qDebug() << "Player touches pig";
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
    FreePig new_pig(10, 10);
    new_pig.setX(rand() % geometry().width());
    new_pig.setY(rand() % geometry().height());
    return new_pig;
}

MainWindow::~MainWindow()
{

}
