#include "choose.h"
#include "ui_choose.h"
QString choose::strname="";
choose::choose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(6,190,182, 200), stop:1 rgba(2,142,161, 200));");
    ui->lineEdit->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->pushButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:10px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    this->resize(390,120);
}

choose::~choose()
{
    delete ui;
}

void choose::on_pushButton_clicked()
{
    strname=ui->lineEdit->text();
    netwindow * net = new netwindow;
    net->show();
    this->close();
}

