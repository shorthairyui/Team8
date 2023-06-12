#include "start.h"
#include "ui_start.h"

start::start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(6,190,182, 200), stop:1 rgba(2,142,161, 200));");
    ui->pushButton->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                                "border: none;border-radius:15px;}"
                                                "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                                "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_2->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                                "border: none;border-radius:15px;}"
                                                "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                                "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_3->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                                "border: none;border-radius:15px;}"
                                                "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                                "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->frame->setStyleSheet("border: none;border-radius:15px;""background-color: rgb(255,255,255);");
    //ui->closebutton->setStyleSheet("QPushButton{color: rgb(0,0,0);background-color: rgb(255,255,255);"
     //                            "border: none;border-radius:3px;}");
    //ui->widget->setStyleSheet("border: none;border-radius:15px;""background-color: rgb(255,255,255);");
    this->setWindowTitle(QStringLiteral("开始界面"));
    QIcon logo("D:/QQT/untitled3/logo.ico");
        this->setWindowIcon(logo);

//    player = new QMediaPlayer;
//    audioOutput = new QAudioOutput;
//    player->setAudioOutput(audioOutput);
//    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
//    player->setSource(QUrl::fromLocalFile("C:\\Users\\pc\\Desktop\\start.mp3"));
//    audioOutput->setVolume(50);
//    player->setLoops(INFINITY);
//    player->play();
    resize(760,500);
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_clicked()
{
    MainWindow *win = new MainWindow;
    win->show();
    this->close();


}


void start::on_pushButton_2_clicked()
{
    setting *set = new setting;
    set->show();
    this->close();
}



void start::on_pushButton_3_clicked()
{
    choose * net = new choose;
    net->show();
    this->close();
}

