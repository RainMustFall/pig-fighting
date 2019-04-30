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
    std::vector<Person> players = {{450, 120, 50, 20},{905, 200, 50, 20}};
    std::list<FreePig> free_pigs = {{100, 10}, {400, 10}};
    std::list<ShotPig> flying_pigs = {};
    std::vector<Ground>ground = {{0, 300, 50, 500}, {600, 450, 50, 350}, {0, 530, 150, 980}, {955, 0, 550, 100}};
};

#endif // MAINWINDOW_H
