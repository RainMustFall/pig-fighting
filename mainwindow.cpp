#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "HERE! ";
    startTimer(10);
}

void MainWindow::timerEvent(QTimerEvent *) {
    bool hits = false;
    for (auto& item:ground) {
        if (player.Hits(item)) {
            player.position_.y = item.yPos() - player.Height();
            hits = true;
        }
    }
    if (hits) {
        player.moveVector_.y = std::min(0, player.moveVector_.y);
    } else {
        player.moveVector_.y ++;
    }
    player.UpdatePosition();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *) {
    //qDebug() << "HERE3";
    QPainter p;
    p.begin(this);
    player.Draw(p);
    for (auto& item:ground) {
        item.Draw(p);
    }
    p.end();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A: player.moveVector_.x = -4; break;
    case Qt::Key_D: player.moveVector_.x = 4; break;
    case Qt::Key_W:
        for (auto& item:ground) {
            if (player.Hits(item)) {
                player.moveVector_.y = -17;
            }
        }
        break;
    default: return;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_A: player.moveVector_.x = 0; break;
    case Qt::Key_D: player.moveVector_.x = 0; break;
    default: return;
    }
}

MainWindow::~MainWindow()
{

}
