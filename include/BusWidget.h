//
// Created by ricardo on 2022/6/28.
//

#ifndef AUTO_BUS_GUI_BUS_WIDGET_H
#define AUTO_BUS_GUI_BUS_WIDGET_H
#include "QGraphicsPixmapItem"
#include "QTransform"

#include "PosPair.h"

class BusWidget
{
public:
    QGraphicsPixmapItem *item;


    explicit BusWidget();

    ~BusWidget();

    void ResetBusPos(PosPair *s);

private:
    PosPair *pos_pairs = nullptr;
};


#endif //AUTO_BUS_GUI_BUS_WIDGET_H
