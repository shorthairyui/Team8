#ifndef ITEM_H
#define ITEM_H

#include <QPoint>

class Item
{
public:
    Item();
    Item(QPoint pt, bool b);
    Item(const Item & t1)
    {
        this->color=t1.color;
        this->itpoint=t1.itpoint;
        this->what_block=t1.what_block;
    }
    //一些方便操作private变量的接口
    QPoint getpoint();
    bool getcolor() ;
    void changepiont(QPoint itt);
    void putblock(int numm){what_block=numm;}
    int getblock(){return what_block;}
    void changecolor(){color=!color;}
    //这个是为了contain判断方便，不然不能用contain！
    bool operator ==(const Item &item) const
        {
            return (color == item.color && itpoint == item.itpoint);
        }
    Item & operator =(const Item t1)
    {
        this->color=t1.color;
        this->itpoint=t1.itpoint;
        this->what_block=t1.what_block;
        return *this;
    }
    QPoint itpoint;
    bool color;
    int what_block;

};

#endif // ITEM_H

