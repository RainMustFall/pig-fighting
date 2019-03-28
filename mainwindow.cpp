#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameobject.h"
#include "ground.h"
#include "person.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    ~MainWindow() override;

private:
    Person player = {0, 0, 50, 20};
    std::vector<Ground>ground = {{0, 200, 50, 500}, {600, 300, 50, 500}};
};

#endif // MAINWINDOW_H
