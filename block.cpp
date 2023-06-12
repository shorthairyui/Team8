#include "block.h"

int block::rolll=9;
block::block()
{

}

void block::add(Item itm)
{
    item_block.append(itm);
}

void block::put_block(int id)
{
   int siz;
   siz=item_block.size();
   item_block[siz-1].putblock(id);


}

int block::getqi(QVector<Item> item)  //每一个块都可以判断是否有气，气是每一个小块的属性
{
    QPoint ri(1,0);
    QPoint le(-1,0);
    QPoint dnn(0,1);
    QPoint upp(0,-1);
    Item itm;
    int flag=0;
    for(int i=0;i<item_block.size();i++)  //对于块中的每一个棋子
    {
        itm=item_block[i];
        itm.itpoint+=ri;
        if(!item.contains(itm))
        {
            itm.changecolor();
            if(!item.contains(itm))
            {
                if(rolll!=13)    //13路和11,9路起始点不一样
                {
                    if(itm.itpoint.x()>=1&&itm.itpoint.y()>=1&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)//限制在边界以内
                    {
                        flag++;
                    }
                }else
                {
                    if(itm.itpoint.x()>=0&&itm.itpoint.y()>=0&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }
            }
        }
        itm=item_block[i];
        itm.itpoint+=le;
        if(!item.contains(itm))
        {
            itm.changecolor();
            if(!item.contains(itm))
            {
                if(rolll!=13)
                {
                    if(itm.itpoint.x()>=1&&itm.itpoint.y()>=1&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }else
                {
                    if(itm.itpoint.x()>=0&&itm.itpoint.y()>=0&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }
            }
        }
        itm=item_block[i];
        itm.itpoint+=dnn;
        if(!item.contains(itm))
        {
            itm.changecolor();
            if(!item.contains(itm))
            {
                if(rolll!=13)
                {
                    if(itm.itpoint.x()>=1&&itm.itpoint.y()>=1&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }else
                {
                    if(itm.itpoint.x()>=0&&itm.itpoint.y()>=0&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }
            }
        }
        itm=item_block[i];
        itm.itpoint+=upp;
        if(!item.contains(itm))
        {
            itm.changecolor();
            if(!item.contains(itm))
            {
                if(rolll!=13)
                {
                    if(itm.itpoint.x()>=1&&itm.itpoint.y()>=1&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }else
                {
                    if(itm.itpoint.x()>=0&&itm.itpoint.y()>=0&&
                            itm.itpoint.x()<=rolll&&itm.itpoint.y()<=rolll)
                    {
                        flag++;
                    }
                }
            }
        }
    }
    return flag;
}


