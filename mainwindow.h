#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constants.h"
#include "person.h"
#include "ground.h"
#include "shotpig.h"

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

//private:
    std::vector<Person> players = {{450, 120},
                                   {800, 200}};

    std::list<FreePig> free_pigs = {{100, 10},
                                    {400, 10}};

    std::list<ShotPig> flying_pigs = {};

    std::vector<Ground>ground = {{-146, 160, 30, 400},
                                 {223, 46, 115, 30},
                                 {587, 130, 30, 282},
                                 {327, 327, 30, 282},
                                 {935, 327, 30, 282},
                                 {1193, 160, 30, 282},
                                 {1068, 476, 30, 282},
                                 {-52, 486, 30, 282},
                                 {122, 656, 30, 1190}};
};

#endif // MAINWINDOW_H
