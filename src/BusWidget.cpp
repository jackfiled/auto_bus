//
// Created by ricardo on 2022/6/28.
//

#include "BusWidget.h"

BusWidget::BusWidget()
{
    item = new QGraphicsPixmapItem(QPixmap(":/picture/bus.png"));

    // 设置缩放
    double bus_scale = 0.1;
    QTransform transform;
    transform.scale(bus_scale, bus_scale);
    item->setTransform(transform);
}

BusWidget::~BusWidget()
{
    delete item;
}

void BusWidget::ResetBusPos(PosPair *s)
{
    pos_pairs = s;

    item->setPos(s[0].GetBusPosX(), s[0].GetBusPosY());
}
