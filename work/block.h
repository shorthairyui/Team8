#ifndef BLOCK_H
#define BLOCK_H

#include<item.h>
#include<QVector>
#include<QPoint>
#include "item.h"

class block
{
public:
    block();
    block(Item it){item_block.append(it);}
    // 一些操作私有变量的函数
    int getnumber(){return num;}
    void add(Item itm);
    void putnumber(int nnum){num=nnum;}
    void put_block(int id);
    int getqi(QVector<Item> item);
    QVector <Item> getvector(){return item_block;}
    static void putrolll(int a){rolll=a;}
    //QVector <int> friendblock;废案
private:
     int num;//块的编号
     static int rolll;
     QVector<Item> item_block;

};

#endif // BLOCK_H
