#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(6,190,182, 200), stop:1 rgba(2,142,161, 200));");
    ui->lineEdit->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");//边框粗细-颜色-圆角设置
    ui->lineEdit_2->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:1px solid rgb(20,196,188);border-radius:10px;");//边框粗细-颜色-圆角设置
    ui->lineEdit_3->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:1px solid rgb(20,196,188);border-radius:10px;");//边框粗细-颜色-圆角设置
    ui->pushButton->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                  "border: none;border-radius:10px;}"
                                  "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                  "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_2->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:10px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_3->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:10px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_4->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    QIcon logo("D:/QQT/untitled3/logo.ico");
        this->setWindowIcon(logo);
    this->setWindowTitle(QStringLiteral("设置"));
    ui->frame->setStyleSheet("border: none;border-radius:15px;""background-color: rgb(255,255,255);");

}
int setting::shenm=10;
int setting::cishu=3;
int setting::roll=9;
setting::~setting()
{
    delete ui;
}

void setting::on_pushButton_clicked()
{
    QString aa;
    int a;
    aa=ui->lineEdit->text();
    bool ok;
    a=aa.toInt(&ok,10);
    if(a<=30)
    {shenm=a;}
    else{
        QMessageBox::warning(this,"警告","你设置了一个非法的超时时长",QMessageBox::Yes);
    }
}


void setting::on_pushButton_2_clicked()
{
    QString aa;
    int a;
    aa=ui->lineEdit_2->text();
    bool ok;
    a=aa.toInt(&ok,10);
    if(a<=5)
    {cishu=a;}
    else{
        QMessageBox::warning(this,"警告","你设置了一个非法的超时次数",QMessageBox::Yes);
    }

}


void setting::on_pushButton_3_clicked()
{
    start *w=new start;
    w->show();
    this->close();
}


void setting::on_pushButton_4_clicked()
{
    QString aa;
    int a;
    aa=ui->lineEdit_3->text();
    bool ok;
    a=aa.toInt(&ok,10);
    if(a!=9&&a!=11&&a!=13)
    {
        QMessageBox::warning(this,"警告","你设置了一个非法的棋盘行数",QMessageBox::Yes);
    }else
    {
        roll=a;
        block::putrolll(a);
    }
}

