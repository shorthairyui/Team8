#ifndef START_H
#define START_H

#include <QDialog>
#include<QTimer>
#include "mainwindow.h"
#include "setting.h"
#include <QMediaPlayer>
#include<QSoundEffect>
#include<QAudioOutput>
#include"netwindow.h"
#include"choose.h"
namespace Ui {
class start;
}

class start : public QDialog
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //void on_closebutton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::start *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};

#endif // START_H
