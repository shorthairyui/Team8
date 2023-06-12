#include "netwindow.h"
#include "ui_netwindow.h"
#define SIMULATION_COUNT 1000
int suicideflag=0;
netwindow::netwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::netwindow)
{
    ui->setupUi(this);
    board=new Board;
    board->net=net();
    name=choose::strname;
    ui->lineEdit_6->setText(name);
    ui->battle->setDisabled(true);
    ui->giveinButton->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->breakButton->setDisabled(true);
    server = new NetworkServer(this);
    soclient = new NetworkSocket(new QTcpSocket(), this);

    connect(server,&QTcpServer::newConnection,this,[=](){
       QMessageBox::information(this,"链接","连接成功",QMessageBox::Yes);
       ui->giveinButton->setDisabled(false);
       ui->pushButton->setDisabled(false);
       ui->breakButton->setDisabled(false);
    });
    connect(soclient, &NetworkSocket::receive, this, &netwindow::recievedata2);
    connect(soclient->base(), &QAbstractSocket::disconnected, [=]() {
        QMessageBox::critical(this, tr("Connection lost"), tr("Connection to server has closed"));
        board->itemlist.clear();
        update();
        timer3->stop();
        timer4->stop();
    });
    connect(server, &NetworkServer::receive,this,&netwindow::recievedata1);
    ui->frame->setStyleSheet("border: none;border-radius:15px;""background-color: rgb(255,255,255);");
    ui->lineEdit_3->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->lineEdit_4->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->giveinButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:10px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->breakButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:10px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->backButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->battle->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->lineEdit_5->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->lineEdit_6->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->record->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->listen->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->port->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->pushButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->ip->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:10px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->connect->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_2->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    //以上ui设计参考网上一篇文章，详见阶段报告1.
    QIcon logo("D:/QQT/untitled3/logo.ico");
        this->setWindowIcon(logo);
    this->setWindowTitle(QStringLiteral("不围棋"));
    switch(setting::getroll())//根据棋盘的大小确定窗口的大小
    {
    case 9:
        resize(500,410);
        break;
    case 11:
        resize(500,450);
        break;
    case 13:
        resize(500,450);
        break;
    }
    ui->lineEdit_3->setText(QString::number(setting::getshenm()));//根据设置里的数字确定lineedit里的初始值
    ui->lineEdit_4->setText(QString::number(setting::getshenm()));
    timeri=0;//初始化总计时
    timerj=0;
    timerk=setting::getshenm();//初始化黑白读秒
    timerp=setting::getshenm();
    blacktime=setting::getcishu();//初始化黑白的读秒次数
    whitetime=setting::getcishu();
    timer3=new QTimer(this);
    timer4=new QTimer(this);
    connect(timer3,&QTimer::timeout,[=](){  //后两个是读秒

            timerk--;
            QString num;
            num=QString::number(timerk);
            ui->lineEdit_3->setText(num);
            if(timerk==0)                     //如果读秒为0了，那么就减一次读秒次数。然后输出一次“超时几次”
            {
                blacktime--;
                if(blacktime==0)
                {
                    timer3->stop();
                    if(board->colorflag)
                    {
                        QString strTip("黑棋超时判负！");
                        QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
                        board->itemlist.clear();//清空所有落子
                        board->tozero();
                    }else
                    {
                        NetworkData data(OPCODE::TIMEOUT_END_OP,"","");
                        if(board->serverflag==0)
                        {
                            server->send(client,data);
                        }
                        else{
                            soclient->send(data);
                        }
                        board->timeoutflag=1;
                    }
                    board->nowitemcolor = 1;
                }
                timerk=setting::getshenm();  //恢复
            }
        });
    connect(timer4,&QTimer::timeout,[=](){   //同上

        timerp--;
        QString num;
        num=QString::number(timerp);
        ui->lineEdit_4->setText(num);
        if(timerp==0)                     //如果读秒为0了，那么就减一次读秒次数。然后输出一次“超时几次”
        {
            whitetime--;
            if(whitetime==0)
            {
                timer4->stop();
                if(board->colorflag)
                {
                    QString strTip("白棋超时判负！");
                    QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
                    board->itemlist.clear();//清空所有落子
                    board->tozero();
                }else
                {
                    NetworkData data(OPCODE::TIMEOUT_END_OP,"","");
                    if(board->serverflag==0)
                    {
                        server->send(client,data);
                    }
                    else{
                        soclient->send(data);
                    }
                    board->timeoutflag=1;
                }
                board->nowitemcolor = 1;
            }
            timerp=setting::getshenm();  //恢复
        }
    });

}

void netwindow::DrawChessBroad(){
    QPainter painter(this);
    QPen pen;//画笔
    QBrush brush(QColor(141,238,238));//画刷并设置颜色
    pen.setColor(QColor(0,0,0));//定义画笔颜色
    pen.setWidth(2);//设置画笔的宽度
    painter.setPen(pen);//添加画笔
    painter.setBrush(brush);//添加画刷
    if(setting::getroll()!=13)     //为了美观，当棋盘是9*9和11*11的时候把它往中间画一点
    {
        painter.drawRect(1.5*25,1.5*25,(setting::getroll()-1)*25,(setting::getroll()-1)*25);
        for(int i = 1;i<setting::getroll()+1;i++)
        {
            painter.drawLine((i+0.5)*25,25*1.5,(i+0.5)*25,(setting::getroll()+0.5)*25);
            painter.drawLine(25*1.5,(i+0.5)*25,(setting::getroll()+0.5)*25,(i+0.5)*25);
        }
    }else
    {
        painter.drawRect(1.5*25,1.5*25,(setting::getroll()-1)*25,(setting::getroll()-1)*25);
        for(int i = 0;i<setting::getroll();i++)
        {
            painter.drawLine((i+0.5)*25,0,(i+0.5)*25,(setting::getroll())*25);
            painter.drawLine(0,(i+0.5)*25,(setting::getroll())*25,(i+0.5)*25);
        }
    }

}

QPoint Board::around(Item it)
{
    Item it1 = it;//通过it1来获取当前棋子
    int r[4]={0,0,0,0};
    int i;
    QPoint ri(1,0);
    QPoint le(-1,0);
    QPoint dnn(0,1);
    QPoint upp(0,-1);
    int flag = 0;
    it1.itpoint+=ri;
    if(itemlist.contains(it1)){r[0]=1;flag++;}  //contain顺便判断了是不是一个颜色的。
    it1.itpoint-=ri;
    it1.itpoint+=le;
    if(itemlist.contains(it1)){r[1]=1;flag++;}
    it1.itpoint-=le;
    it1.itpoint+=dnn;
    if(itemlist.contains(it1)){r[2]=1;flag++;}
    it1.itpoint-=dnn;
    it1.itpoint+=upp;
    if(itemlist.contains(it1)){r[3]=1;flag++;}
    it1.itpoint-=upp;
    for( i=0;i<4;++i)
    {
        if(r[i]!=0)break;  //如果周围有相同颜色的小块，那么其实优先级是ri le dnn upp
    }
    if(i==4)i--;
    QPoint ac(flag,i);//flag意思是四周有几个同样颜色的棋子，i的意思是同样颜色的在哪里
    return ac;//返回棋子以便于判断是否属于其他块
}

void netwindow::DrawItems(){
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    pen.setColor(Qt::transparent);//设置画笔颜色为透明色
    painter.setPen(pen);
    //循环我们的所有落子，并绘制出来
    for(int i = 0;i<board->itemlist.size();i++)
    {
        Item item = board->itemlist[i];
        if(i!=board->itemlist.size()-1)
        {
            if(item.getcolor())
            {
                painter.setBrush(Qt::black);
            }else {
                painter.setBrush(Qt::white);
            }
            //获取棋子的位置
            QPoint ptCenter((item.itpoint.x()+0.5)*25,(item.itpoint.y()+0.5)*25);
            //绘制棋子，棋子的半径为宽高的一半
            painter.drawEllipse(ptCenter,(25/2)-2,(25/2)-2);
        }
        else
        {
            if(item.getcolor())
            {
                painter.setBrush(QColor(25,25,112));
            }else {
                painter.setBrush(QColor(255,248,220));
            }
            QPoint ptCenter((item.itpoint.x()+0.5)*25,(item.itpoint.y()+0.5)*25);

            painter.drawEllipse(ptCenter,(25/2)-2,(25/2)-2);
        }

    }

}

void netwindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pt;//定义一个点
    int x = event->pos().x();//获取鼠标点击的x坐标
    int y = event->pos().y();//获取鼠标点击的y坐标
    pt.setX(x/25);//设置棋子x坐标
    pt.setY(y/25);//设置棋子y坐标
    if(setting::getroll()!=13)  //为了美观做出了一定的牺牲，需要判断是不是在棋盘外，在棋盘外就直接返回。
    {
        if(pt.x()>(setting::getroll()+0.5)||pt.y()>(setting::getroll()+0.5)||pt.x()<0.5||pt.y()<0.5)
        {
            return;
        }
    }else
    {
        if(pt.x()>setting::getroll()||pt.y()>setting::getroll())
        {
            return;
        }
    }
    if(board->nowitemcolor!=board->colorflag)
    {
        QMessageBox::information(this,"警告","it's not ur turn!!",QMessageBox::Yes);
        return;
    }
    if(board->colorflag==0&&board->itemlist.size()==0)
    {
        QMessageBox::information(this,"警告","black first",QMessageBox::Yes);
        return;
    }
    for(int i = 0;i<board->itemlist.size();i++){
        Item item = board->itemlist[i];
        if(item.getpoint() == pt){
            return;
        }
    }
    Item item(pt,board->colorflag);//设定棋子坐标及颜色
    //棋子的计数装置
    if(board->colorflag)
    {
        board->blacknum++;
    }
    else
    {
        board->whitenum++;
    }
    QString ss,ss1;
    int x1,y1;
    char ch;
    x1=item.itpoint.x();
    y1=item.itpoint.y();
    ch=y1+64;
    ss.append(ch);
    ss.append(QString::number(x1));
    ss.append(" ");
    NetworkData data(OPCODE::MOVE_OP,ss,ss1.number(QDateTime::currentMSecsSinceEpoch()));
    if(board->serverflag==0)
    {
        server->send(client,data);//把这个数据发送过去
    }
    else{
        soclient->send(data);
    }
      //judge函数判断它是哪个块的，块的编号是棋子类的属性，所以不用返回值。
    //board->itemlist.append(item);  //添加棋子到所有的棋子。
    board->simple(item);
    update();
    if(!board->nowitemcolor)  //计时器部分
    {
        ui->lineEdit_3->setText(QString::number(setting::getshenm()));
        timerk=setting::getshenm();
        timer4->start(1000);
        timer3->stop();
    }
    else
    {
        ui->lineEdit_4->setText(QString::number(setting::getshenm()));
        timerp=setting::getshenm();
        timer3->start(1000);
        timer4->stop();
    }
    board->nowitemcolor = !board->nowitemcolor;//切换棋子颜色
    if(aiflag==1)
    {
        ai();
    }
    QString str1;
    str1.append(board->allstr());
    QFile log("d:\\a.txt");
    log.open(QFile::WriteOnly);
    std::string stdstr = str1.toStdString();
    const char* arr = stdstr.c_str();
    log.write(arr);
}

void netwindow::paintEvent(QPaintEvent *event)
{
    DrawChessBroad();
    DrawItems();
}

void netwindow::tozero()
{
    QString num;
    ui->lineEdit_3->setText(num.number(timerk));
    ui->lineEdit_4->setText(num.number(timerp));
    update();
    ui->record->clear();
    ui->battle->setDisabled(false);
    timerk=setting::getshenm();//重置黑白读秒
    timerp=setting::getshenm();
    aiflag=0;
    timer3->stop();
    timer4->stop();
}

int Board::find(Item & it)  //?莫名其妙的函数
{
    int i;
    for(i=0;i<itemlist.size();i++)
    {
        if(it.getpoint()==itemlist[i].getpoint())break;
    }
    return i;
}

void Board::judge(Item &item)
{
    QPoint a = around(item);
    QPoint ri(1,0);
    QPoint le(-1,0);
    QPoint dnn(0,1);
    QPoint upp(0,-1);
    if(a.x()>0)
    {
        int p,q;Item temp_ite;
        switch (a.y()) {
        case 0:
            temp_ite=item;
            temp_ite.itpoint+=ri;
            p=find(temp_ite);
            q=itemlist[p].getblock();//获取他是哪个块
            item.putblock(q);
            m_blocks[q].add(item);
            break;
        case 1:
             temp_ite=item;
            temp_ite.itpoint+=le;
            p=find(temp_ite);
            temp_ite=itemlist[p];
            q=temp_ite.getblock();//获取他是哪个块
            item.putblock(q);
            m_blocks[q].add(item);
            break;
        case 2:
             temp_ite=item;
            temp_ite.itpoint+=dnn;
            p=find(temp_ite);
            temp_ite=itemlist[p];
            q=temp_ite.getblock();//获取他是哪个块
            item.putblock(q);
            m_blocks[q].add(item);
            break;
        case 3:
             temp_ite=item;
            temp_ite.itpoint+=upp;
            p=find(temp_ite);
            temp_ite=itemlist[p];
            q=temp_ite.getblock();//获取他是哪个块
            item.putblock(q);
            m_blocks[q].add(item);
            break;
        }
    }
    else                          //如果边上不存在相同颜色的棋子，那就新建一个块
    {
        block bl(item);
        bl.putnumber(numofblock1);
        bl.put_block(numofblock1);
        item.putblock(numofblock1);
        numofblock1++;
        m_blocks.append(bl);
    }
}

QVector<int> Board::getitemaround(int idnt)  //这是找到不同颜色的周围小块的函数，不需要递归。
{
    int id;
    //int flag=0;
    QVector <int> num;
    QVector <Item> n_items,h_items;
    h_items=m_blocks[idnt].getvector();
    for(int i=0;i<h_items.size();i++)
    {
        Item item;
        item=h_items[i];
        n_items=getdiffitem(item);
        for(int j=0;j<n_items.size();j++)
        {
            id=n_items[j].getblock();
            if(!num.contains(id))
            {
                num.append(id);
            }
        }

    }
    return num;
}

QVector<Item> Board::getdiffitem(Item item)//getitemaround 的辅助函数
{
    QPoint ri(1,0);//定义四种方向
    QPoint le(-1,0);
    QPoint dnn(0,1);
    QPoint upp(0,-1);
    Item itm;
    QVector <Item> n_items;//临时棋子空间

    for(int i=0;i<itemlist.size();i++)
    {
        itm=itemlist[i];//取出一个棋子
        if(itm.getpoint()==(item.getpoint()+ri)&&
                itm.getcolor()!=item.getcolor())
        {
            n_items.append(itm);
        }
        if(itm.getpoint()==(item.getpoint()+le)&&
                itm.getcolor()!=item.getcolor())
        {
            n_items.append(itm);
        }
        if(itm.getpoint()==(item.getpoint()+dnn)&&
                itm.getcolor()!=item.getcolor())
        {
            n_items.append(itm);
        }
        if(itm.getpoint()==(item.getpoint()+upp)&&
                itm.getcolor()!=item.getcolor())
        {
            n_items.append(itm);
        }
    }
    return n_items;
}

void Board::statistic()       //结算前的统计函数
{
    for(int i=0;i<itemlist.size();i++)
    {
        Item item=itemlist[i];
        int x,y;
        char ch;
        x=item.getpoint().x();
        y=item.getpoint().y();
        ch=x+65;                   //把它记录成字母
        if(item.getcolor())
        {
           b_allstr.append(ch);
           b_allstr.append(QString::number(y));
           b_allstr.append(" ");
        }else
        {
            w_allstr.append(ch);
            w_allstr.append(QString::number(y));
            w_allstr.append(" ");
        }

    }
}

QString Board::jiesuan()        //结算函数，用于数据统计和最后结算界面字符串的生成
{
    statistic();
    QString str1;
    if(nowitemcolor){str1.append(" 白方获胜！\n");}
    else {str1.append(" 黑方获胜！\n");}
    str1.append("黑棋落子：\n");
    str1.append(b_allstr);
    str1.append("\n白棋落子：\n");
    str1.append(w_allstr);
    return str1;
}

int Board::select(Node *node)
{
    int selectedChildIndex = 0;
    double bestScore = 0.0;
    for (int i = 0; i < node->children.size(); ++i) {
        Node* child = node->children[i];
        if(child->wins>bestScore)
        {
            bestScore=child->wins;
            selectedChildIndex=i;
        }
    }
    return selectedChildIndex;
}

QVector<int> Board::getitemarounddiff(int idnt,QVector <int> &num) //找到周围相同颜色的棋子，因为只要是周围就共享气所以这个可以递归。
{
    int aa;
    QVector <int> num1;
    QVector <Item> n_items,h_items;
    int flag=0;
    h_items=m_blocks[idnt].getvector();//获取对应块类的名单
    for(int i=0;i<h_items.size();i++)
    {
        Item item;
        item=h_items[i];
        n_items=getsameitem(item);
        for(int j=0;j<n_items.size();j++)
        {
            aa=n_items[j].getblock();//获取每一个相同棋子属于哪个块
            if(!num.contains(aa))//如果遇到新的，就加进来
            {
                num1.append(aa);
                flag++;
            }
        }
    }
    num.append(num1);
    if(flag!=0)
    {
       for(int i=num.size();i<num1.size();i++)
       {
           num.append(getitemarounddiff(num[i],num));

       }
    }
    return num;
}

QVector<Item> Board::getsameitem(Item item)//与getdiffitem相似，不过返回的是一个棋子周围颜色相同的棋子
{
    QPoint ri(1,0);//定义四种方向
    QPoint le(-1,0);
    QPoint dnn(0,1);
    QPoint upp(0,-1);
    Item itm;
    QVector <Item> n_items;//临时棋子空间

    for(int i=0;i<itemlist.size();i++)
    {
        itm=itemlist[i];//取出一个棋子
        if(itm.getpoint()==(item.getpoint()+ri)&&
                itm.getcolor()==item.getcolor())//这里的！=变成了==，说明返回的是颜色相同的棋子
        {
            n_items.append(itm);
        }
        if(itm.getpoint()==(item.getpoint()+le)&&
                itm.getcolor()==item.getcolor())
        {
            n_items.append(itm);
        }
        if(itm.getpoint()==(item.getpoint()+dnn)&&
                itm.getcolor()==item.getcolor())
        {
            n_items.append(itm);
        }
        if(itm.getpoint()==(item.getpoint()+upp)&&
                itm.getcolor()==item.getcolor())
        {
            n_items.append(itm);
        }
    }
    return n_items;
}
void netwindow::win(int a)    //为了简化mousepressevent写的函数
{    
    timer3->stop();
    timer4->stop();
    if(a==1)
    {

        QMessageBox::information(this,"胜负","白棋胜利",QMessageBox::Yes);
    }
    if(a==0)
    {

        QMessageBox::information(this,"胜负","黑棋胜利",QMessageBox::Yes);
    }
    if(a==3)
    {
        suicideflag++;
        board->itemlist.pop_back();
        if(suicideflag>20)
        {
            if(board->colorflag==0)
            {
                NetworkData data(OPCODE::GIVEUP_OP,name,"");
                if(board->serverflag==0)
                {
                    server->send(client,data);//把这个数据发送过去
                }
                else{
                    soclient->send(data);
                }
            }
            board->itemlist.clear();
            update();
            board->tozero();
        }
        return;
    }

    //board->itemlist.pop_back();
    board->itemlist.clear();
    update();
    board->tozero();
}

void netwindow::ai()
{
//    aiboard= new Board;
//    aiboard->itemlist.append(board->itemlist);
//    aiboard->colorflag=board->colorflag;
//    aiboard->nowitemcolor=board->nowitemcolor;
//    aiboard->numofblock1=board->numofblock1;
//    aiboard->m_blocks.append(board->m_blocks);
//    // 构建根节点
//    Node* rootNode = new Node();
//    rootNode->item.color=!board->colorflag;
//    if(aiboard->itemlist.size()!=0)rootNode->item=aiboard->itemlist.last();
//    for (int i = 0; i < 200; ++i) {
//        //pauseLock.lock();
//        Node* currentNode = rootNode;
//        aiboard= new Board;
//        aiboard->itemlist.append(board->itemlist);
//        aiboard->colorflag=board->colorflag;
//        aiboard->nowitemcolor=board->nowitemcolor;
//        aiboard->numofblock1=board->numofblock1;
//        aiboard->m_blocks.append(board->m_blocks);
//        // 选择
//        while (!currentNode->children.empty()) {
//            int selectedChildIndex = aiboard->selectBestChild(currentNode, 5 , rootNode->visits);
//            currentNode = currentNode->children[selectedChildIndex];
//        }

//        // 扩展
//        if (currentNode->visits > 0) {
//            aiboard->expand(currentNode);
//        }
//        // 模拟
//        double simulationResult = aiboard->simulateRandomPlayout(currentNode);

//        // 反向传播
//        aiboard->backpropagation(currentNode, simulationResult);
//        delete aiboard;
//        //pauseLock.unlock();

//    }
//    int num=0;
//    num=board->select(rootNode);
//    Item item(rootNode->children[num]->item);
    aiboard= new Board;
    aiboard->itemlist.append(board->itemlist);
    aiboard->colorflag=board->colorflag;
    aiboard->nowitemcolor=board->nowitemcolor;
    aiboard->numofblock1=board->numofblock1;
    aiboard->m_blocks.append(board->m_blocks);
    Item item=aiboard->getrandom(aiboard->itemlist);
    aiboard->judge(item);
    aiboard->itemlist.append(item);
    int flag=0;
    while(aiboard->simple(item,1)==!board->colorflag||board->mycontain(item)==1||aiboard->simple(item,1)==3)
    {
        flag++;
        aiboard->itemlist.pop_back();
        aiboard->colorflag=!aiboard->colorflag;
        item=aiboard->getrandom(aiboard->itemlist);
        aiboard->judge(item);
        aiboard->itemlist.append(item);
        if(flag>200)
        {
            NetworkData data(OPCODE::GIVEUP_OP,name,"");
            if(board->serverflag==0)
            {
                server->send(client,data);//把这个数据发送过去
            }
            else{
                soclient->send(data);
            }
            board->tozero();
            return;
        }
    }
//  Item item=aiboard->getrandom(aiboard->itemlist);
    board->judge(item);  //judge函数判断它是哪个块的，块的编号是棋子类的属性，所以不用返回值。
    board->itemlist.append(item);  //添加棋子到所有的棋子。
    //board->simple(item);
    QString ss,ss1;
    int x1,y1;
    char ch;
    x1=item.itpoint.x();
    y1=item.itpoint.y();
    ch=y1+64;
    ss.append(ch);
    ss.append(QString::number(x1));
    NetworkData data(OPCODE::MOVE_OP,ss,ss1.number(QDateTime::currentMSecsSinceEpoch()));
    if(board->serverflag==0)
    {
        server->send(client,data);//把这个数据发送过去
    }
    else{
        soclient->send(data);
    }

    if(!board->nowitemcolor)  //计时器部分
    {
        ui->lineEdit_3->setText(QString::number(setting::getshenm()));
        timerk=setting::getshenm();
        timer4->start(1000);
        timer3->stop();
    }
    else
    {
        ui->lineEdit_4->setText(QString::number(setting::getshenm()));
        timerp=setting::getshenm();
        timer3->start(1000);
        timer4->stop();
    }
    board->nowitemcolor = !board->nowitemcolor;
    update();
}

void Board::simple(Item &item)
{
    judge(item);  //judge函数判断它是哪个块的，块的编号是棋子类的属性，所以不用返回值。
    itemlist.append(item);  //添加棋子到所有的棋子。
    block qi;             //创建一个临时块对象
    int id;               //临时块编号变量
    id=item.getblock();   //找到新下的棋子是哪个块的
    qi=m_blocks.at(id);   //把这个块找到
    int little_block_qi;   //小块的气
    little_block_qi=qi.getqi(itemlist);
    QVector <int> diffbkid;                     //放的是异色块的名单
    QVector <int> samebkid;
    QVector <int> num;
    diffbkid=getitemaround(id);//diffbkid是周围的异色块
    num.append(id);
    samebkid=getitemarounddiff(id,num);//samebkid是周围的同色块
    int pflag=0;
    int nflag=0;
    int flag[diffbkid.size()]={0};//flag是计数器
    QVector <QVector <int> > bigblock; //bigblock是周围大块的容器，每一个元素都是一个大块

    for(int i=0;i<diffbkid.size();i++)
    {
        QVector <int> num1;
        num1.append(diffbkid[i]);
        bigblock.append(getitemarounddiff(diffbkid[i],num1));

    }
    //判定是否赢
    //getitemaround或者diff这两个函数经过改造获取的是所有相邻的小块编号。所以，所有相邻的小块其实就是一个大块
    for(int i=0;i<diffbkid.size();i++)
    {
        for(int j=0;j<bigblock[i].size();j++)
        {
            if(m_blocks[bigblock[i][j]].getqi(itemlist)!=0)flag[i]++; //第i块大块是不是有qi，如果没有，那么flagi就是0
        }
    }
    for(int i=0;i<diffbkid.size();i++)
    {
        if(flag[i]==0)pflag++;//当所有的边大块有的时候至少一个没气pflag才不是0，都有气就是0
    }
    for(int j=0;j<samebkid.size();j++)
    {
        if(m_blocks[samebkid[j]].getqi(itemlist)!=0)nflag++;//如果所有同色小块都由绮，那肯定能活
    }
    if(little_block_qi==0)//如果本棋子属于的小块qi为零
    {
        if(nflag!=0)//如果和小块相邻的同颜色小块还有qi（其实就是一大块）
        {
            //return;//就继续游戏(wrong)
            //万一对方没气了呢？？
            if(pflag!=0)
            {
                net->win(!item.getcolor());  //如果边上的异颜色大块也没气了，就是同时没气对方被吃，你还是输
                return;
            }else
                {
                return;
            }
        }
        else                                //如果边上的同颜色块也没qi了，也就是说必然有胜负关系出现
        {
            //如果边上的异颜色大块还有气
            net->win(3);      //如果边上的异颜色大块也没气了，就是同时没气对方被吃，你还是输
            return;
        }
    }
    //如果我本身的小块qi还有不是0那也不用考虑其他的，就看边上的黑大块是不是0就好
    else{
        if(pflag!=0) //边上的黑块
        {
            net->win(item.getcolor());
            return;
        }
    }
    //nowitemcolor = !nowitemcolor;//切换棋子颜色
}

int Board::simple(Item &item,int a)
{
    //itemlist.append(item);  //添加棋子到所有的棋子。
    block qi;             //创建一个临时块对象
    int id;               //临时块编号变量
    id=item.getblock();   //找到新下的棋子是哪个块的
    qi=m_blocks.at(id);   //把这个块找到
    int little_block_qi;   //小块的气
    little_block_qi=qi.getqi(itemlist);
    QVector <int> diffbkid;                     //放的是异色块的名单
    QVector <int> samebkid;
    QVector <int> num;
    diffbkid=getitemaround(id);//diffbkid是周围的异色块
    num.append(id);
    samebkid=getitemarounddiff(id,num);//samebkid是周围的同色块
    int pflag=0;
    int nflag=0;
    int flag[diffbkid.size()]={0};//flag是计数器
    QVector <QVector <int> > bigblock; //bigblock是周围大块的容器，每一个元素都是一个大块

    for(int i=0;i<diffbkid.size();i++)
    {
        QVector <int> num1;
        num1.append(diffbkid.at(i));
        bigblock.append(getitemarounddiff(diffbkid.at(i),num1));

    }
    //判定是否赢
    //getitemaround或者diff这两个函数经过改造获取的是所有相邻的小块编号。所以，所有相邻的小块其实就是一个大块
    for(int i=0;i<diffbkid.size();i++)
    {
        for(int j=0;j<bigblock[i].size();j++)
        {
            if(m_blocks[bigblock[i][j]].getqi(itemlist)!=0)flag[i]++; //第i块大块是不是有qi，如果没有，那么flagi就是0
        }
    }
    for(int i=0;i<diffbkid.size();i++)
    {
        if(flag[i]==0)pflag++;//当所有的边大块有的时候至少一个没气pflag才不是0，都有气就是0
    }
    for(int j=0;j<samebkid.size();j++)
    {
        if(m_blocks[samebkid[j]].getqi(itemlist)!=0)nflag++;//如果所有同色小块都由绮，那肯定能活
    }
    if(little_block_qi==0)//如果本棋子属于的小块qi为零
    {
        if(nflag!=0)//如果和小块相邻的同颜色小块还有qi（其实就是一大块）
        {
            //return;//就继续游戏(wrong)
            //万一对方没气了呢？？
            if(pflag!=0)
            {

                return (!item.getcolor());//我输
            }else
                {
                return -1;
            }
        }
        else                                //如果边上的同颜色块也没qi了，也就是说必然有胜负关系出现
        {
                     //如果边上的异颜色大块还有气
            return 3;//(!item.getcolor()); //如果边上的异颜色大块也没气了，就是同时没气对方被吃，你还是输
        }
    }
    //如果我本身的小块qi还有不是0那也不用考虑其他的，就看边上的黑大块是不是0就好
    else{
        if(pflag!=0) //边上的黑块
        {
            return (!item.getcolor());
        }
    }
    return -1;
    //nowitemcolor = !nowitemcolor;//切换棋子颜色
}

void Board::tozero() //归归归归归归归归归零
{
    nowitemcolor = 1;//初始化落子颜色 0 为白色 1为黑色
    numofblock1=0;//初始化块的计数器
    blacknum=0;//初始化黑白棋子的计数器
    whitenum=0;
    net->timeri=0;//初始化总计时
    net->timerj=0;
    readytoplay=0;
    chatflag=0;
    goingflag=0;
    colorflag=0;//这是之后自己选的想要执的颜色，0为白，1为黑，暂时初始化为白色。
    readyflag=0;//0表示ready的信息是对方发出的，1表示这条信息是对方回复的。
    timeoutflag=0;//0表示是我timeout了，1表示是对方。
    guendflag=0;//0表示对方认输，1是我认输。
    serverflag=-1;//0表示我是服务端，1表示我是客户端
    b_allstr.clear();
    w_allstr.clear();
    itemlist.clear();
    net->tozero();

}

void Board::record(NetworkData data,int flag)
{
    QString str;
    if(flag==1)
    {
        str.append("客户端");
    }else
    {
        str.append("服务端");
    }
    str.append(datatostr(data));
    str.append(" data1: ");
    str.append(data.data1);
    str.append(" data2: ");
    str.append(data.data2);
    str.append("\n");
    QFile log("d:\\b.txt");
    log.open(QIODevice::ReadWrite);
    std::string stdstr = str.toStdString();
    const char* arr = stdstr.c_str();
    log.write(arr);
}

QString Board::datatostr(NetworkData data)
{
   QString str;
   if(data.op==OPCODE::CHAT_OP)
   {
       str.append("CHAT_OP");
       return str;
   }
   if(data.op==OPCODE::GIVEUP_END_OP)
   {
       str.append("GIVEUP_END_OP");
       return str;
   }
   if(data.op==OPCODE::GIVEUP_OP)
   {
       str.append("GIVEUP_OP");
       return str;
   }
   if(data.op==OPCODE::LEAVE_OP)
   {
       str.append("LEAVE_OP");
       return str;
   }
   if(data.op==OPCODE::MOVE_OP)
   {
       str.append("MOVE_OP");
       return str;
   }
   if(data.op==OPCODE::READY_OP)
   {
       str.append("READY_OP");
       return str;
   }
   if(data.op==OPCODE::REJECT_OP)
   {
       str.append("REJECT_OP");
       return str;
   }
   if(data.op==OPCODE::SUICIDE_END_OP)
   {
       str.append("SUICIDE_END_OP");
       return str;
   }
   if(data.op==OPCODE::TIMEOUT_END_OP)
   {
       str.append("TIMEOUT_END_OP");
       return str;
   }
   str.append("INCORRECT SIGNAL");
   return str;
}

bool Board::mycontain(Item item)
{
    bool flag=0;
    for(int i=0;i<itemlist.size();i++)
    {
        if(item.itpoint==itemlist[i].itpoint)
        {
            flag=1;
        }
    }
    return flag;
}

void Board::expand(Node *node)
{
    Node * node1;
    for(int i=1;i<10;i++)
    {
        for(int j=1;j<10;j++)
        {
            Item item(QPoint(i,j),!node->item.color);
            if(abs(node->item.itpoint.x()-i)+abs(node->item.itpoint.y()-j)>=5)continue;

            if(!mycontain(item))
            {
                node1=new Node;
                node1->item=item;
                node1->parent=node;
                node->children.append(node1);
            }
        }
    }
}

void Board::backpropagation(Node *node, double result)
{
    Node* current = node;
    while (current != nullptr) {
        current->visits++;
        current->wins += result;
        current = current->parent;
    }
}

double Board::simulateRandomPlayout(Node *node)
{

    Item item(getrandom(itemlist));
    itemlist.append(item);
    while(simple(item,1)==-1)
    {
        item=getrandom(itemlist);
        itemlist.append(item);
    }
    if(simple(item,1)==nowitemcolor)
    {
        return 0.2;
    }
    if(simple(item,1)!=nowitemcolor)
    {
        return -0.1;
    }
    if(simple(item,1)==3)
    {
        return -0.2;
    }
    return 0;
}

int Board::selectBestChild(Node *node, double explorationParameter, double rootnum)
{
    int selectedChildIndex = 0;
    double bestScore = 0.0;

    for (int i = 0; i < node->children.size(); ++i) {
        Node* child = node->children[i];
        double score;
        if(child->visits!=0)
        {
             score = child->wins / child->visits +
                explorationParameter * sqrt(log(rootnum) / child->visits);

        }
        if(child->visits==0)
        {
             score=1.7e300;
        }
        if (score > bestScore) {
            bestScore = score;
            selectedChildIndex = i;
        }
        else if(score==bestScore)
        {
            if(QRandomGenerator::global()->bounded(10)>5)
            {
                bestScore = score;
                selectedChildIndex = i;
            }
        }

    }

    return selectedChildIndex;
}

Item  Board::getrandom(QVector<Item> items)
{
    int x=QRandomGenerator::global()->bounded(9);
    int y=QRandomGenerator::global()->bounded(9);
    Item item;
    item.itpoint.setX(x+1);
    item.itpoint.setY(y+1);
    item.color=colorflag;
    int flag=0;
    while(mycontain(item))
    {
        flag++;
        int x=QRandomGenerator::global()->bounded(9);
        int y=QRandomGenerator::global()->bounded(9);
        item.itpoint.setX(x+1);
        item.itpoint.setY(y+1);
        item.color=colorflag;
        if(flag>82)
        {
            break;
        }
    }
    judge(item);  //judge函数判断它是哪个块的，块的编号是棋子类的属性，所以不用返回值。
    colorflag=!colorflag;
    return item;
}

QString Board::allstr()
{
    QString allstr;
    for(int i=0;i<itemlist.size();i++)
    {
        Item item=itemlist[i];
        int x,y;
        char ch;
        x=item.getpoint().x();
        y=item.getpoint().y();
        ch=x+64;                   //把它记录成字母
        allstr.append(ch);
        allstr.append(QString::number(y));
        allstr.append(" ");
    }
    return allstr;
}

void netwindow::recievedata1(QTcpSocket *mclient, NetworkData data)
{
    client=mclient;
    board->record(data,0);
    if(data.op==OPCODE::READY_OP)
    {
        ui->battle->setDisabled(true);
        QString color;
        if(board->readyflag==0)
        {
            QString data2=data.data2;
            if(QMessageBox::question(this,"对方提问",color.append("客户端想用颜色："+data.data2))==QMessageBox::Yes)//data2里面是想要拿到的颜色，这个可以做一下文章，同时把我们这边的发消息时候的data2写好。
                    //但是因为发data2的时候是请求对局，思考什么时候服务端是可以请求对局的，适时利用disable使得按钮功能齐全。
            {
                cname=data.data1;
                NetworkData mdata(OPCODE::READY_OP,name,"");
                server->send(client,mdata);
                if(data2=="w")
                {
                    board->colorflag=1;
                }else{
                    board->colorflag=0;
                }
                board->goingflag=1;
                timer3->start(1000);
                //ui->battle->setDisabled(false);
            }else
            {
                NetworkData mdata(OPCODE::REJECT_OP,name,"");
                server->send(client,mdata);
                ui->battle->setDisabled(false);
            }
        }else{
            //这里是对方回复，上面是对方申请。
           ui->record->append("对方同意了我们的请求");
           std::ofstream fout("d:\\c.txt",std::ios_base::app);
           fout<< std::endl;
           fout<< "start" << std::endl;
           //timer3->start(1000);//因为黑先所以直接让黑棋开始读秒。
        }
        board->readyflag=0;//只要没点发起申请按钮，所有的ready信息就是对方发出的。
    }

    if(data.op==OPCODE::LEAVE_OP)
    {
        QMessageBox::information(this,"提示","已经断开连接",QMessageBox::Yes);
        client->close();
    }
    if(data.op==OPCODE::MOVE_OP)
    {
        //为什么每次不把最新的棋子信息传过来就好呢？？
        QString str=data.data1;
        char ch;
        ch=str[0].unicode();
        int y=ch-64;
        int x=str[1].digitValue();
        QPoint pt(x,y);
        Item item(pt,!board->colorflag);//颜色问题

        if(board->colorflag)
        {
           board->whitenum++;
        }else
        {
           board->blacknum++;
        }
        update();//更新
        board->simple(item);
        if(!board->nowitemcolor)  //计时器部分
        {
           ui->lineEdit_3->setText(QString::number(setting::getshenm()));
           timerk=setting::getshenm();
           timer4->start(1000);//如果要调整传输过程中的时间，在这里调整最好
           timer3->stop();
        }
        else
        {
           ui->lineEdit_4->setText(QString::number(setting::getshenm()));
           timerp=setting::getshenm();
           timer3->start(1000);
           timer4->stop();
        }
        board->nowitemcolor=!board->nowitemcolor;
        if(aiflag==1)
        {
            ai();
        }

    }
    if(data.op==OPCODE::TIMEOUT_END_OP&&board->timeoutflag==0)//自己超时。
    {
        NetworkData mdata(OPCODE::TIMEOUT_END_OP,"","");
        server->send(client,data);
    }
    if(data.op==OPCODE::TIMEOUT_END_OP&&board->timeoutflag==1)//对方超时。
    {
       if(board->colorflag)
       {
          QString strTip("白棋超时判负！");
          QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
          board->tozero();

       }else{
          QString strTip("黑棋超时判负！");
          QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
          board->tozero();
       }
    }
    if(data.op==OPCODE::GIVEUP_OP)
    {
        NetworkData mdata(OPCODE::GIVEUP_END_OP,"","");
        server->send(client,mdata);
        board->statistic();
        timer3->stop();
        timer4->stop();
        if(board->colorflag)
        {
            board->whitenum++;
            board->w_allstr.append(" G");
        }
        else{
            board->blacknum++;
            board->b_allstr.append(" G");
        }
        QString str;
        if(board->colorflag){str="白方认输";}
        else {str="黑方认输";}
        QString str1;
        str1.append(str);
        if(!board->colorflag){str1.append(" 白方获胜！\n");}
        else {str1.append(" 黑方获胜！\n");}
        str1.append("黑棋落子：\n");
        str1.append(board->b_allstr);
        str1.append("\n白棋落子：\n");
        str1.append(board->w_allstr);
        QMessageBox::information(this,str,str1,QMessageBox::Yes);
        board->tozero();
    }
    if(data.op==OPCODE::GIVEUP_END_OP)
    {
       if(!board->guendflag)
       {
           NetworkData mdata(OPCODE::GIVEUP_END_OP,"","");
            server->send(client,mdata);
       }
    }
    if(data.op==OPCODE::CHAT_OP)
    {
       QString Msg =data.data1;
       ui->record->append(cname+":" + Msg);
    }
    if(data.op==OPCODE::REJECT_OP)
    {
        ui->record->append("对方拒绝了我们的对战申请");
        ui->battle->setDisabled(false);
    }
    if(data.op==OPCODE::SUICIDE_END_OP)
    {
        QMessageBox::information(this,"提示","对方判断你自杀",QMessageBox::Yes);
    }
}

netwindow::~netwindow()
{
    delete ui;
}

void netwindow::on_giveinButton_clicked()  //认输按钮
{
    if(board->nowitemcolor!=board->colorflag)
    {
        return;
    }
    NetworkData data(OPCODE::GIVEUP_OP,name,"");
    if(board->serverflag==0)
    {
        server->send(client,data);
    }
    else{
        soclient->send(data);
    }
    board->guendflag=1;//我方发送
    timer3->stop();
    timer4->stop();
    board->statistic();
    if(!board->colorflag)
    {
        board->whitenum++;
        board->w_allstr.append(" G");
    }
    else{
        board->blacknum++;
        board->b_allstr.append(" G");
    }
    QString str;
    if(!board->colorflag){str="白方认输";}
    else {str="黑方认输";}
    QString str1;
    str1.append("黑棋落子：\n");
    str1.append(board->b_allstr);
    str1.append("\n白棋落子：\n");
    str1.append(board->w_allstr);
    QMessageBox::information(this,str,str1,QMessageBox::Yes);
    board->tozero();
}

void netwindow::on_breakButton_clicked()   //断开连接按钮
{
    if(board->nowitemcolor)
    {
        timer3->stop();
    }
    else{
          timer4->stop();
    }
    if(board->serverflag==0)
    {
        board->tozero();
        NetworkData data(OPCODE::LEAVE_OP,"","");
        server->send(client,data);
        //client->close();
        ui->battle->setDisabled(false);
    }else
    {
        board->tozero();
        NetworkData data(OPCODE::LEAVE_OP,"","");
        soclient->send(data);
    }
}

void netwindow::on_backButton_clicked()   //返回按钮槽函数
{
    start *sta=new start;
    sta->show();
    this->close();
}

void netwindow::on_pushButton_clicked()
{
    //if(chatflag==0)chatflag=1;
    if(board->serverflag==0)
    {
        QString sendMsg = ui->lineEdit_5->text();
        NetworkData data(OPCODE::CHAT_OP,sendMsg,"");
        server->send(client,data);
        ui->record->append(name+":" + sendMsg);
        ui->lineEdit_5->clear();
    }else
    {
//        if(chatflag==0)chatflag=1;
        QString sendMsg = ui->lineEdit_5->text();
        NetworkData data(OPCODE::CHAT_OP,sendMsg,"");
        soclient->send(data);
        ui->record->append(name+":" + sendMsg);
        ui->lineEdit_5->clear();
    }

}


void netwindow::on_battle_clicked()
{

    if(board->goingflag==1)return;
    if(board->serverflag==0)
    {
        if(QMessageBox::question(this,"询问","你想要执？(yes是黑)")==QMessageBox::Yes)
        {
            NetworkData data(OPCODE::READY_OP,name,"b");
            server->send(client,data);
            board->colorflag=1;
        }else
        {
            NetworkData data(OPCODE::READY_OP,name,"w");
            server->send(client,data);
            board->colorflag=0;
        }
        board->readyflag=1;
    }else{
        if(QMessageBox::question(this,"询问","你想要执？(yes是黑)")==QMessageBox::Yes)
        {
            NetworkData data(OPCODE::READY_OP,name,"b");
            soclient->send(data);
            board->colorflag=1;
        }else
        {
            NetworkData data(OPCODE::READY_OP,name,"w");
            soclient->send(data);
            board->colorflag=0;
        }
        //ui->battle->setDisabled(true);
        board->readyflag=1;
    }
    ui->battle->setDisabled(true);
}


void netwindow::on_listen_clicked()
{
    unsigned short port = ui->port->text().toInt();
    // 设置服务器监听
    server->listen(QHostAddress::Any, port);
    //ui->listen->setEnabled(false); 这个功能以后在实现。
    board->serverflag=0;
}

void netwindow::recievedata2(NetworkData data)
{
    board->record(data,1);
    if(data.op==OPCODE::READY_OP)
    {
        ui->battle->setDisabled(true);
        QString color;
        if(board->readyflag==0)
        {
            if(QMessageBox::question(this,"对方提问",color.append("服务端想用颜色："+data.data2))==QMessageBox::Yes)//data2里面是想要拿到的颜色，这个可以做一下文章，同时把我们这边的发消息时候的data2写好。
                    //但是因为发data2的时候是请求对局，思考什么时候服务端是可以请求对局的，适时利用disable使得按钮功能齐全。
            {
                cname=data.data1;
                NetworkData mdata(OPCODE::READY_OP,name,"");
                soclient->send(mdata);
                if(data.data2=="w")
                {
                    board->colorflag=1;
                }else{
                    board->colorflag=0;
                }
                timer3->start(1000);
            }else
            {
                NetworkData mdata(OPCODE::REJECT_OP,name,"");
                soclient->send(mdata);
                //ui->battle->setDisabled(false);
            }
        }else{
            //这里是对方回复，上面是对方申请。
           ui->record->append("对方同意了我们的请求");
           std::ofstream fout("d:\\c.txt",std::ios_base::app);
           fout<<std::endl;
           fout<< "start"<<std::endl;
           //timer3->start(1000);//因为黑先所以直接让黑棋开始读秒。
        }
        board->readyflag=0;//只要没点发起申请按钮，所有的ready信息就是对方发出的。
    }
    if(data.op==OPCODE::LEAVE_OP)
    {
        QMessageBox::information(this,"提示","已经断开连接",QMessageBox::Yes);
        NetworkData mdata(OPCODE::LEAVE_OP,"","");
        soclient->send(mdata);
    }
    if(data.op==OPCODE::MOVE_OP)
    {
        //为什么每次不把最新的棋子信息传过来就好呢？？
        QString str=data.data1;
        char ch;
        ch=str[0].unicode();
        int y=ch-64;
        int x=str[1].digitValue();
        QPoint pt(x,y);
        Item item(pt,!board->colorflag);//颜色问题

        if(board->colorflag)
        {
           board->whitenum++;
        }else
        {
           board->blacknum++;
        }
        update();//更新
        board->simple(item);
       if(!board->nowitemcolor)  //计时器部分
       {
           ui->lineEdit_3->setText(QString::number(setting::getshenm()));
           timerk=setting::getshenm();
           timer4->start(1000);//如果要调整传输过程中的时间，在这里调整最好  later.
           timer3->stop();
       }
       else
       {
           ui->lineEdit_4->setText(QString::number(setting::getshenm()));
           timerp=setting::getshenm();
           timer3->start(1000);
           timer4->stop();
       }
       board->nowitemcolor=!board->nowitemcolor;
       if(aiflag==1)
       {
           ai();
       }
    }
    if(data.op==OPCODE::TIMEOUT_END_OP&&board->timeoutflag==0)//自己超时。
    {
       NetworkData mdata(OPCODE::TIMEOUT_END_OP,"","");
       soclient->send(mdata);
    }
    if(data.op==OPCODE::TIMEOUT_END_OP&&board->timeoutflag==1)//对方超时。
    {
       if(!board->colorflag)
       {
          QString strTip("黑棋超时判负！");
          QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
          board->tozero();
       }else{
          QString strTip("白棋超时判负！");
          QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
          board->tozero();
       }
    }
    if(data.op==OPCODE::GIVEUP_OP)
    {
        NetworkData ndata(OPCODE::GIVEUP_END_OP,"","");
        soclient->send(ndata);
        board->statistic();
        timer3->stop();
        timer4->stop();
        if(board->colorflag)
        {
            board->whitenum++;
            board->w_allstr.append(" G");
        }
        else{
            board->blacknum++;
            board->b_allstr.append(" G");
        }
        QString str;
        if(!board->colorflag){str="黑方认输";}
        else {str="白方认输";}
        QString str1;
        str1.append(str);
        if(!board->colorflag){str1.append(" 白方获胜！\n");}
        else {str1.append(" 黑方获胜！\n");}
        str1.append("黑棋落子：\n");
        str1.append(board->b_allstr);
        str1.append("\n白棋落子：\n");
        str1.append(board->w_allstr);
        QMessageBox::information(this,str,str1,QMessageBox::Yes);
        board->tozero();
    }
    if(data.op==OPCODE::GIVEUP_END_OP)
    {
       if(!board->guendflag)
       {
           NetworkData mdata(OPCODE::GIVEUP_END_OP,"","");
           soclient->send(mdata);
       }
    }
    if(data.op==OPCODE::CHAT_OP)
    {
       QString Msg =data.data1;
       ui->record->append(cname+":" + Msg);
    }
    if(data.op==OPCODE::REJECT_OP)
    {
        ui->record->append("对方拒绝了我们的对战申请");
        ui->battle->setDisabled(false);
    }
    if(data.op==OPCODE::SUICIDE_END_OP)
    {
        QMessageBox::information(this,"提示","对方判断你自杀",QMessageBox::Yes);
    }
}

void netwindow::on_connect_clicked()
{
    QString str = ui->ip->text();
    unsigned short port = ui->port->text().toInt();
    soclient->hello(str,port);
    board->serverflag=1;
    ui->battle->setDisabled(false);
    ui->giveinButton->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->breakButton->setDisabled(false);
}


void netwindow::on_pushButton_2_clicked()
{
    aiflag=!aiflag;
    ai();
}


Board::Board()
{
    readytoplay=0;
    chatflag=0;
    colorflag=1;//这是之后自己选的想要执的颜色，0为白，1为黑，暂时初始化为白色。
    readyflag=0;//0表示ready的信息是对方发出的，1表示这条信息是对方回复的。
    timeoutflag=0;//0表示是我timeout了，1表示是对方。
    guendflag=0;//0表示对方认输，1是我认输。
    serverflag=-1;//0表示我是服务端，1表示我是客户端
    goingflag=0;//对局不在进行是0，正在进行是1
    nowitemcolor = 1;//初始化落子颜色 0 为白色 1为黑色
    numofblock1=0;//初始化块的计数器
    blacknum=0;//初始化黑白棋子的计数器
    whitenum=0;
    itemlist.clear();
    m_blocks.clear();


}

Board::~Board()
{

}
