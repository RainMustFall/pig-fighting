#include "mainwindow.h"
#include "constants.h"
#include "health_field.h"
#include "themostmainwindow.h"
#include "soundplayer.h"
#include <QPainter>
#include <chrono>
#include <cstdlib>
#include <QMouseEvent>
#include <QDebug>
#include <thread>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      controller_(new FieldController(this)),
      parent_(dynamic_cast<TheMostMainWindow*>(parent)),
      cur_theme(TextureType::GRASS)
{
    /*f_player->setPlaylist(f_playlist);
    f_playlist->addMedia(QUrl("qrc:resources/sounds/background.mp3"));
    f_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    f_player->setVolume(15);*/

    DrawBackground();
    setFocus();
    qDebug() << "HERE! ";
    //pig_caught.setSource(QUrl::fromLocalFile(":/resources/sounds/pig_caught.mp3"));
    //pig_caught.setVolume(0.5f);
}

void MainWindow::SetTimer() {
    is_start = true;
    timer_id = startTimer(9);
}

void MainWindow::StopTimer() {
    killTimer(timer_id);
}

void MainWindow::GameOver(int player) {
    parent_->GameOver(player);
}

void MainWindow::NewGame(TextureType type) {
    cur_theme = type;
    DrawBackground();
    setFocus();
    delete controller_;
    controller_ = new FieldController(this, type);
    SetTimer();
}

void MainWindow::timerEvent(QTimerEvent *) {
    controller_->UpdateTimer();
    controller_->UpdatePlayers();
    controller_->AddPigs();
    controller_->UpdateFreePigs();
    controller_->UpdateFlyingPigs();
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    controller_->onPaintingStarted(p);
    p.end();
}

void MainWindow::DrawHint(QPainter& painter){
    const QRectF rectangle2 = {kScreenWidth- 355,kScreenHeight - 180, 345, 122};
    QImage image2;
    image2.load(":/resources/textures/instruction2.png");
    painter.drawImage(rectangle2,
                      image2);
    const QRectF rectangle1 = {10,kScreenHeight - 180, 345, 122};
    QImage image1;
    image1.load(":/resources/textures/instruction1.png");
    painter.drawImage(rectangle1,
                      image1);
}

void MainWindow::DrawBackground() {
    QString bg_dir = bg_dirs_[static_cast<unsigned>(cur_theme)];
    QPixmap bkgnd(kTexturesPath + bg_dir + "/background.png");
    bkgnd = bkgnd.scaled(kScreenWidth, kScreenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p(palette());
    p.setBrush(QPalette::Background, bkgnd);
    setAutoFillBackground(true);
    setPalette(p);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Escape) {
      parent_->Pause(false);
    } else {
        controller_->onKeyPressed(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    controller_->onKeyReleased(event);
}

MainWindow::~MainWindow()
{

}
