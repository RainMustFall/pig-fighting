#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constants.h"
#include "person.h"
#include "ground.h"

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
    Person player = {450, 120, 50, 20};
    std::vector<Ground>ground = {{0, 200, 50, 500}, {600, 400, 50, 500}, {0, 530, 100, 980}, {965, 0, 550, 0}};
};

#endif // MAINWINDOW_H
