#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include "constants.h"
#include "person.h"
#include "ground.h"
#include "shotpig.h"
#include "health_field.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void ThrowPig(Person& player);
    ~MainWindow() override;
    FreePig GeneratePig();

    Animation pig_running_l;
    Animation pig_running_r;
    Animation pig_flying_l;
    Animation pig_flying_r;

    std::vector<Person> players = {{450, 120, "player_1"},
                                   {800, 200, "player_2"}};

    std::list<FreePig> free_pigs;

    std::list<ShotPig> flying_pigs = {};


    std::list<HealthField> health_fields = {
           {10,10,100, &players[0]},
           {kScreenWidth - 110,10,100, &players[1]}
       };

    std::vector<Ground>ground = {{-146, 160, 30, 420},
                                 /*{223, 46, 115, 30},*/
                                 {587, 130, 30, 270},
                                 {327, 327, 30, 270},
                                 {935, 327, 30, 270},
                                 {1193, 160, 30, 270},
                                 {1068, 486, 30, 270},
                                 {-52, 486, 30, 270},
                                 {122, 656, 30, 1200}};

    int time = 0;

    QSoundEffect pig_caught;
    int timer_id;
    bool isTimerActive = true;

    void SetTimer();

    void NewGame();

    bool SoundOn = true;
};

#endif // MAINWINDOW_H
