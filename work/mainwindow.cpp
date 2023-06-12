#include "mainwindow.h"
#include "ui_mainwindow.h"
int numofblock=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    board= new Board;
    ui->frame->setStyleSheet("border: none;border-radius:15px;""background-color: rgb(255,255,255);");
    ui->lineEdit->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:1px solid rgb(20,196,188);border-radius:10px;");
    ui->lineEdit_2->setStyleSheet("font: 25 12pt '微软雅黑 Light';" //字体
                                  "color: rgb(31,31,31);"		//字体颜色
                                  "padding-left:10px;"       //内边距-字体缩进
                                  "background-color: rgb(255, 255, 255);" //背景颜色
                                  "border:1px solid rgb(20,196,188);border-radius:10px;");
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
    ui->restartButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:10px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->backButton->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->ai->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:9px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->ai_2->setStyleSheet("QPushButton{font: 25 9pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
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
        resize(500,300);
        break;
    case 11:
        resize(500,350);
        break;
    case 13:
        resize(500,350);
        break;
    }
    ui->lineEdit_3->setText(QString::number(setting::getshenm()));//根据设置里的数字确定lineedit里的初始值
    ui->lineEdit_4->setText(QString::number(setting::getshenm()));
    board->nowitemcolor = 1;//初始化落子颜色 0 为白色 1为黑色
    numofblock=0;//初始化块的计数器
    blacknum=0;//初始化黑白棋子的计数器
    whitenum=0;
    timeri=0;//初始化总计时
    timerj=0;
    timerk=setting::getshenm();//初始化黑白读秒
    timerp=setting::getshenm();
    blacktime=setting::getcishu();//初始化黑白的读秒次数
    whitetime=setting::getcishu();
    board->itemlist.clear();//清空我们的落子
    timer1=new QTimer(this);//新的计时器
    timer2=new QTimer(this);
    timer3=new QTimer(this);
    timer4=new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){    //一些计时器连接函数
            timeri++;
            QString num;
            num=QString::number(timeri);

            ui->lineEdit->setText(num);
        });
    connect(timer2,&QTimer::timeout,[=](){    //前两个是总计时
            timerj++;
            QString num;
            num=QString::number(timerj);

            ui->lineEdit_2->setText(num);
        });
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
                    timer1->stop();
                    timer3->stop();
                    QString strTip("黑棋超时判负！");
                    QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
                    board->itemlist.clear();//清空所有落子
                    if(QMessageBox::question(this,"new?","是否开始新的一局")==QMessageBox::Yes)
                    {
                        MainWindow *min=new MainWindow;
                        min->show();
                        this->close();
                    }else
                    {
                        start *min=new start;
                        min->show();
                        this->close();
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
            if(timerp==0)
            {
                whitetime--;
                if(whitetime==0)
                {
                    timer2->stop();
                    timer4->stop();
                    QString strTip("白棋超时判负！");
                    QMessageBox::information(this,"提示超时",strTip,QMessageBox::Yes);
                    board->itemlist.clear();//清空所有落子
                    if(QMessageBox::question(this,"new?","是否开始新的一局")==QMessageBox::Yes)
                    {
                        MainWindow *min=new MainWindow;
                        min->show();
                        this->close();
                    }else
                    {
                        start *min=new start;
                        min->show();
                        this->close();
                    }
                    board->nowitemcolor = 1;

                }
                timerp=setting::getshenm();

            }


    });
    timer1->start(1000);   //总计时器开始计时
    timer3->start(1000);
}

void MainWindow::DrawChessBroad(){
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

void MainWindow::DrawItems(){
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

void MainWindow::mousePressEvent(QMouseEvent *event)
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
    for(int i = 0;i<board->itemlist.size();i++){
        Item item = board->itemlist[i];
        if(item.getpoint() == pt){
            return;
        }
    }
    Item item(pt,board->nowitemcolor);//设定棋子坐标及颜色
    std::ofstream fout("d:\\a.txt",std::ios_base::app);
    if(board->itemlist.size()==0)
    {
        fout<< std::endl;
        fout<< "new";
    }
    char ax=(x/25)+64;
    fout << ax<<y/25;
//    board->itemlist.append(item);
    board->judge(item);
    board->itemlist.append(item);
    int winflag=board->simple(item,1);

    if(winflag!=-1&&winflag!=3)
    {
//         QString endstr=board->jiesuan();
//          if(winflag==1)
//        {
//            QMessageBox::information(this,"胜负",endstr,QMessageBox::Yes);
//        }
//        if(winflag==0)
//        {
//            QMessageBox::information(this,"胜负",endstr,QMessageBox::Yes);
//        }
//        board->itemlist.clear();
//        update();
//        MainWindow* min=new MainWindow;
//        min->show();
//        this->close();
        QMessageBox::information(this,"提示","不要走这儿",QMessageBox::Yes);
        Item temitem=board->itemlist.last();
        if(board->m_blocks[temitem.getblock()].getvector().size()==1)
        {
            board->numofblock1--;
            board->m_blocks.pop_back();
        }else
        {
            board->m_blocks[temitem.getblock()].getvector().pop_back();
        }
        board->itemlist.pop_back();
        return;

    }
    //棋子的计数装置
    if(board->nowitemcolor)
    {
        blacknum++;
    }
    else
    {
        whitenum++;
    }

    if(board->nowitemcolor)  //计时器部分
    {
        ui->lineEdit_3->setText(QString::number(setting::getshenm()));
        timerk=setting::getshenm();
        timer1->stop();
        timer2->start(1000);timerj++;ui->lineEdit_2->setText(QString::number(timerj));
        timer4->start(1000);
        timer3->stop();
    }
    else
    {
        ui->lineEdit_4->setText(QString::number(setting::getshenm()));
        timerp=setting::getshenm();
        timer2->stop();
        timer1->start(1000);timeri++;ui->lineEdit->setText(QString::number(timeri));
        timer3->start(1000);
        timer4->stop();
    }
    update();
    board->nowitemcolor = !board->nowitemcolor;//切换棋子颜色
    if(aiflag==1)
    {
        ai();
    }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    DrawChessBroad();
    DrawItems();
    //update();
}

void MainWindow::ai()
{
    aiboard= new Board;
    aiboard->itemlist.append(board->itemlist);
    aiboard->colorflag=board->colorflag;
    aiboard->nowitemcolor=board->nowitemcolor;
    aiboard->numofblock1=board->numofblock1;
    aiboard->m_blocks.append(board->m_blocks);
//    // 构建根节点
//    Node* rootNode = new Node();
//    if(aiboard->itemlist.size()!=0)rootNode->item=aiboard->itemlist.last();
//    for (int i = 0; i < 100; ++i) {
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
//    int num=board->select(rootNode);
//    Item item(rootNode->children[num]->item);
    Item item=aiboard->getrandom(aiboard->itemlist);
    board->judge(item);
    board->itemlist.append(item);
    //board->simple(item);
    if(board->nowitemcolor)  //计时器部分
    {
        ui->lineEdit_3->setText(QString::number(setting::getshenm()));
        timerk=setting::getshenm();
        timer1->stop();
        timer2->start(1000);timerj++;ui->lineEdit_2->setText(QString::number(timerj));
        timer4->start(1000);
        timer3->stop();
    }
    else
    {
        ui->lineEdit_4->setText(QString::number(setting::getshenm()));
        timerp=setting::getshenm();
        timer2->stop();
        timer1->start(1000);timeri++;ui->lineEdit->setText(QString::number(timeri));
        timer3->start(1000);
        timer4->stop();
    }
    board->nowitemcolor = !board->nowitemcolor;
//    board->colorflag=!board->colorflag;
    //update();
//    if(aiflag==1)
//    {
//        ai();
    //    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_giveinButton_clicked()  //认输按钮
{

    board->statistic();
    if(board->nowitemcolor)
    {
        timer1->stop();
        timer3->stop();
        blacknum++;
        board->b_allstr.append(" G");
    }
    else{
        timer2->stop();
        timer4->stop();
        whitenum++;
        board->w_allstr.append(" G");
    }
    QString str;
    if(board->nowitemcolor){str="黑方认输";}
    else {str="白方认输";}
    QString str1;
    str1.append(str);
    if(board->nowitemcolor){str1.append(" 白方获胜！\n");}
    else {str1.append(" 黑方获胜！\n");}
    str1.append("黑棋落子：\n");
    str1.append(board->b_allstr);
    str1.append("\n白棋落子：\n");
    str1.append(board->w_allstr);
    str1.append("\n黑棋平均思考时间：\n");
    str1.append(QString::number(b_ave));
    str1.append("\n白棋平均思考时间：\n");
    str1.append(QString::number(w_ave));

    QMessageBox::information(this,str,str1,QMessageBox::Yes);
    QFile log("d:\\a.txt");
    //log.open(QIODevice::ReadWrite);
    log.open(QFile::WriteOnly|QFile::Truncate);
    std::string stdstr = str1.toStdString();
    const char* arr = stdstr.c_str();
    log.write(arr);
    board->itemlist.clear();
    if(QMessageBox::question(this,"new?","是否开始新的一局")==QMessageBox::Yes)
    {
        MainWindow *min=new MainWindow;
        min->show();
        this->close();
    }else
    {
        start *min=new start;
        min->show();
        this->close();
    }


}

void MainWindow::on_restartButton_clicked()   //重新开始按钮
{
    if(board->nowitemcolor)
    {
        timer1->stop();
        timer3->stop();
    }
    else{
          timer2->stop();
          timer4->stop();

    }
    board->itemlist.clear();
    QMessageBox::information(this,"确认","开始新的一局",QMessageBox::Yes);

    MainWindow *min=new MainWindow;
    min->show();
    this->close();
}

void MainWindow::on_backButton_clicked()   //返回按钮槽函数
{
    if(board->nowitemcolor)
    {
        timer1->stop();
        timer3->stop();
    }
    else{
          timer2->stop();
          timer4->stop();

    }
    start *sta=new start;
    sta->show();
    this->close();
}


void MainWindow::on_ai_clicked()
{
//    mythread->start();
//    update();
    aiflag=!aiflag;
    ai();
}



void MainWindow::on_review_clicked()
{
    timer1->stop();
    timer2->stop();
    timer3->stop();
    timer4->stop();
    std::ifstream fin;
    fin.open("d:\\a.txt",std::ios_base::in|std::ios_base::out);
    std::string str;
    while(std::getline(fin,str))
    {

    }

    reviewstr=str;
}

void MainWindow::review(std::string str)
{
    QString qstr;
    qstr=QString::fromStdString(str);
    int colorflag=1;
    for(int i=3;i<qstr.size();i=i+2)
    {
        int x=str[i]-64;
        int y=str[i+1]-48;
        Item item(QPoint(x,y),colorflag);
        board->itemlist.append(item);
        colorflag=!colorflag;
    }
}


void MainWindow::on_pushButton_clicked()
{
    int x=reviewstr[2*reviewnownum+3]-64;
    int y=reviewstr[2*reviewnownum+4]-48;
    Item item(QPoint(x,y),board->nowitemcolor);
    board->itemlist.append(item);
    board->nowitemcolor=!board->nowitemcolor;
    update();
    if(reviewnownum<board->itemlist.size())
    {
        reviewnownum++;
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    board->itemlist.pop_back();
    board->nowitemcolor=!board->nowitemcolor;
    update();
    if(reviewnownum>0)
    {
        reviewnownum--;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString qstr;
    qstr=QString::fromStdString(reviewstr);
//    int colorflag=1;
//    for(int i=3;i<qstr.size();i=i+2)
//    {
//        int x=reviewstr[2*reviewnownum+3]-64;
//        int y=reviewstr[2*reviewnownum+4]-48;
//        Item item(QPoint(x,y),colorflag);
//        board->itemlist.append(item);
//        colorflag=!colorflag;
//    }
    review(reviewstr);
    update();
    reviewnownum=(qstr.size()-3)/2;
}


void MainWindow::on_ai_2_clicked()
{
    int color=board->colorflag;
    if(board->itemlist.size()!=0)
    {
        while(board->simple(board->itemlist.last(),1)==-1)
        {
            ai();
            board->colorflag=!board->colorflag;
        }
    }else
    {
        ai();
        board->colorflag=!board->colorflag;
        update();
        while(board->simple(board->itemlist.last(),1)==-1)
        {
            ai();
            board->colorflag=!board->colorflag;
            update();
        }
    }
    board->colorflag=color;

}


void MainWindow::on_pushButton_4_clicked()
{
    timer1->stop();
    timer2->stop();
    timer3->stop();
    timer4->stop();
    while(board->itemlist.size()>reviewnownum)
    {
        board->itemlist.pop_back();
    }
    update();
}

