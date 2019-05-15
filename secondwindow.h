#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    enum class PauseCase {
        FIRSTWIN,
        SECONDWIN,
        ESCAPE
    };


    SecondWindow(MainWindow *parent = nullptr, PauseCase type = PauseCase::ESCAPE);
    ~SecondWindow();

    PauseCase type;
    MainWindow *parent;
    bool ThirdButtonSoundTurnOn;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_windowIconTextChanged(const QString &iconText);

private:
    Ui::SecondWindow *ui;


};

#endif // SECONDWINDOW_H
