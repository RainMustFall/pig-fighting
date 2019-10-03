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
    parent_(dynamic_cast<TheMostMainWindow*>(parent)),
    cur_theme(TextureType::GRASS),
    controller_(new FieldController(this))
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

void MainWindow::NewGame(TextureType type) {
    cur_theme = type;
    DrawBackground();
    setFocus();

    qDebug() << "starting new game";
    delete controller_;
    controller_ = new FieldController(this);

    qDebug() <<"new";
    paused = false;
    SetTimer();
}

void MainWindow::Pause(const QString &reason) {
    if (!paused) {
        parent_->ui->new_game->setEnabled(true);
        parent_->ui->comboBox->setEnabled(true);
        parent_->ui->pause->setText("Продолжить");
        killTimer(timer_id);
        parent_->ui->label_2->setText(reason);
    } else {
        setFocus();
        parent_->ui->new_game->setEnabled(false);
        parent_->ui->comboBox->setEnabled(false);
        parent_->ui->pause->setText("Пауза");
        parent_->ui->label_2->setText("");
        SetTimer();
    }
    if(reason != "Пауза"){
        parent_->ui->pause->setEnabled(false);
    }

    paused = not(paused);
}

void MainWindow::timerEvent(QTimerEvent *) {

    controller_->UpdateTimer();

    controller_->UpdatePlayers();

    qDebug() << "started cycle of timer";
    controller_->AddPigs();

    controller_->UpdateFreePigs();

    controller_->UpdateFlyingPigs();
    qDebug() << "cycle of timer";
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p;
    p.begin(this);
    controller_->onPaintingStarted(p);
    p.end();
}

void MainWindow::drawPlayingObjects(QPainter& p, const ObjectSet& objects) {
    for (const Person& player : objects.players) {
        player.Draw(p);
    }

    for (const HealthField& field : objects.health_fields) {
        field.Draw(p);
    }

    for (const auto& item : objects.ground) {
        item.Draw(p);
    }

    for (const FreePig& item : objects.free_pigs) {
        item.Draw(p);
    }
    for (const ShotPig& item : objects.flying_pigs) {
        item.Draw(p);
    }
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
    std::vector<QString>bg_dirs = {"grass", "sand", "cave", "snow"};

    qDebug() << "Drawing background";
    QPixmap bkgnd(":/resources/textures/" + bg_dirs[static_cast<unsigned>(cur_theme)] + "/background.png");
    bkgnd = bkgnd.scaled(kScreenWidth, kScreenHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p(palette());
    p.setBrush(QPalette::Background, bkgnd);
    setAutoFillBackground(true);
    setPalette(p);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    controller_->onKeyPressed(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    controller_->onKeyReleased(event);
}

MainWindow::~MainWindow()
{

}
