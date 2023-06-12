#ifndef NETWINDOW_H
#define NETWINDOW_H

#include <QDialog>
#include <QVector>
#include <QTimer>
#include "item.h"
#include "start.h"
#include "block.h"
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QIcon>
#include <networkserver.h>
#include<networkdata.h>
#include<networksocket.h>
#include"choose.h"
#include<QThread>
#include<QMutex>
namespace Ui {
class netwindow;
}
class Node;
class Board;
class MyThread;
class netwindow : public QDialog
{
    Q_OBJECT

public:
    explicit netwindow(QWidget *parent = 0);
    ~netwindow();
    //绘制方面的函数
    void DrawChessBroad();//绘制棋盘
    void DrawItems();//绘制棋子
    void mousePressEvent(QMouseEvent *event);//鼠标点击落子
    void paintEvent(QPaintEvent *event);
    netwindow * net()
    {
        return this;
    }
    void tozero();//方便再来一局的函数
    void win(int a);//判断输赢最后的结果函数
    void ai();//ai搜索过程的函数
    bool aiflag=0;
public slots:
    void recievedata1(QTcpSocket * mclient,NetworkData data);
    void recievedata2(NetworkData data);

private slots:
    void on_giveinButton_clicked();

    void on_breakButton_clicked();

    void on_backButton_clicked();

    void on_pushButton_clicked();

    void on_battle_clicked();

    void on_listen_clicked();//监听函数

    void on_connect_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::netwindow *ui;
public:
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

    double b_ave;
    double w_ave;
    Board * board;
    Board * aiboard;
    QString name;//服务端用户名
    QString cname;//客户端用户名
    QTcpSocket * client;
    NetworkServer * server;
    NetworkSocket * soclient;

};
class Board:public QObject
{
public:
    Board();
    ~Board();
    //逻辑判断方面函数
    QPoint around(Item it);//judge的辅助函数
    int find(Item &it);//
    void judge(Item &item);//判断棋子是哪个块
    QVector<int> getitemaround(int idnt);//这是找到不同颜色的周围小块的函数，不需要递归。
    QVector<Item> getdiffitem(Item item);//getitemaround 的辅助函数
    QVector<int> getitemarounddiff(int idnt, QVector<int> &num);//找到周围相同颜色的棋子，因为只要是周围就共享气所以这个可以递归。
    QVector<Item> getsameitem(Item item);//与getdiffitem相似，不过返回的是一个棋子周围颜色相同的棋子
    //结算方面函数
    void statistic();//结算的辅助函数
    QString jiesuan();//结算的函数，用于生成结算的字符串
    int select(Node* node);//用于选出ai搜索完下一步下什么棋的函数

    NetworkData transform(QVector<Item> items);//这个和下一个是data和items的相互转换的函数
    QVector<Item> transform(NetworkData data);//但是好像多余了，当时理解的是把当前局面传过去
    void simple(Item &item);//一般的判断输赢函数
    int simple(Item &item, int a);//上一个判断输赢时调用win函数弹出弹窗，这个返回值。这个用于ai
    void tozero();//方便再来一局的函数
    void record(NetworkData data, int flag);//每次收到信息的记录函数，但是因为改了网络文件中的，日志就没必要用这个了
    QString datatostr(NetworkData data);//data向str的转换函数
    bool mycontain(Item item);//自己写的contain函数，因为item重构的==导致颜色也成为判断的条件，这个只要坐标相同就算包含。
    void expand(Node * node);//这是扩展结点的函数，扩展下一步能下的所有位置。
    void backpropagation(Node* node, double result);//反向传播函数，利用parent结点指针，可以完成value和访问次数的反向传播。
    double simulateRandomPlayout(Node *node);//随机模拟函数，在里面调用getrandom直到分出胜负。
    int selectBestChild(Node* node, double explorationParameter, double rootnum);//利用ucb公式计算最好结点。
    Item getrandom(QVector<Item> items);//生成两个随机数，调用mycontain函数。并顺便judge他们的块（不然会有问题）
    QString allstr();//方便最后的结算
public:
    int readytoplay;
    int chatflag;
    int colorflag;
    int readyflag;
    int timeoutflag;
    int guendflag;
    int serverflag;
    int goingflag;
    int numofblock1=0;
    int blacknum;
    int whitenum;
//    readytoplay=0;
//    chatflag=0;
//    colorflag=1;//这是之后自己选的想要执的颜色，0为白，1为黑，暂时初始化为白色。
//    readyflag=0;//0表示ready的信息是对方发出的，1表示这条信息是对方回复的。
//    timeoutflag=0;//0表示是我timeout了，1表示是对方。
//    guendflag=0;//0表示对方认输，1是我认输。
//    serverflag=-1;//0表示我是服务端，1表示我是客户端
//    goingflag=0;//对局不在进行是0，正在进行是1
//    nowitemcolor = 1;//初始化落子颜色 0 为白色 1为黑色
//    numofblock1=0;//初始化块的计数器
//    blacknum=0;//初始化黑白棋子的计数器
//    whitenum=0;
public:
    //一些public变量
    QVector<Item> itemlist;//记录我们的落子
    QVector<block> m_blocks;
    bool nowitemcolor;//记录落子颜色
    QString b_allstr;//最后结算的时候的黑棋序列
    QString w_allstr;//白棋
    netwindow * net;
};

class Node
{
public:
    int visits;
    double wins;//这个相当于value，是算出来的结果
    QVector<Node*> children;
    Node* parent;
    Item item;
    Node() : visits(0), wins(0.0) {parent=NULL;}
    Node(Node & node)
    {
        this->visits=node.visits;
        this->wins=node.wins;
        this->children.append(node.children);
        this->item=node.item;
    }
};



#endif

