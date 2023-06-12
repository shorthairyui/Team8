#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include "item.h"
#include "start.h"
#include "block.h"
#include"netwindow.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QTextStream>
#include<QFile>
#include <QIcon>
#include <fstream>
#include <iostream>
namespace Ui {
class MainWindow;
}
class Board;
class MyThread;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //绘制方面的函数
    void DrawChessBroad();//绘制棋盘
    void DrawItems();//绘制棋子
    void mousePressEvent(QMouseEvent *event);//鼠标点击落子
    void paintEvent(QPaintEvent *event);
    //逻辑判断方面函数
    void ai();
    bool aiflag=0;
    void review(std::string str);
private slots:
    void on_giveinButton_clicked();//放弃按钮

    void on_restartButton_clicked();//重新开始按钮

    void on_backButton_clicked();//返回按钮

    void on_ai_clicked();//ai托管按钮

    void on_review_clicked();//复现准备按钮

    void on_pushButton_clicked();//下一步按钮

    void on_pushButton_2_clicked();//上一步按钮

    void on_pushButton_3_clicked();//播放按钮

    void on_ai_2_clicked();//eve button

    void on_pushButton_4_clicked();//尝试后恢复按钮

private:
    Ui::MainWindow *ui;
    int timerid;
    QTimer *timer1;//黑棋的计时器
    QTimer *timer2;
    QTimer *timer3;
    QTimer *timer4;
    int timeri;
    int timerj;
    int timerk;
    int timerp;
    int blacktime;
    int whitetime;
    int blacknum;
    int whitenum;
    int reviewnownum=0;
    std::string reviewstr;//复现的临时棋子序列
    double b_ave;//黑棋平均思考时间
    double w_ave;
    Board * board;//normal board
    Board * aiboard;//ai board
    MyThread* mythread;//no use
};


//class Board
//{
//public:
//    QPoint around(Item it);
//    int find(Item &it);
//    void judge(Item &item);
//    int Judge(Item &item);
//    QVector<int> getitemaround(int idnt);
//    QVector<Item> getdiffitem(Item item);
//    QVector<int> getitemarounddiff(int idnt, QVector<int> &num);
//    QVector<Item> getsameitem(Item item);
//    //结算方面函数
//    void statistic();
//    QString jiesuan();
//    void win(int a);
//    //一些public变量
//    QVector<Item> itemlist;//记录我们的落子
//    QVector<block> m_blocks;
//    bool nowitemcolor;//记录落子颜色

//    QString b_allstr;
//    QString w_allstr;
//};

#endif // MAINWINDOW_H

