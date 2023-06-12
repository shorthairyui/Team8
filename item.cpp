#include "item.h"

Item::Item()
{

}
Item::Item(QPoint pt, bool b)
{
    itpoint = pt;
    color = b;
}

QPoint Item::getpoint()
{
    return itpoint;
}

bool Item::getcolor()
{
    return color;
}

void Item::changepiont(QPoint itt)
{
   itt=itpoint;
}

