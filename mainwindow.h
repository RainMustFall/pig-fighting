#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "constants.h"
#include "person.h"
#include "ground.h"
#include "shotpig.h"
#include "soundplayer.h"
#include "health_field.h"
#include "fieldcontroller.h"

class TheMostMainWindow;

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
    void drawPlayingObjects(QPainter& p, const ObjectSet&);

    QSoundEffect pig_caught;
    int timer_id;
    bool isTimerActive = true;

    void SetTimer();

    void NewGame(TextureType type);
    void DrawBackground();
    void DrawHint(QPainter& painter);
    void Pause(const QString& reason);

    bool is_start = true;
    bool paused = true;
    TheMostMainWindow* parent_;

    TextureType cur_theme;

private:
    FieldController* controller_;
};

#endif // MAINWINDOW_H
