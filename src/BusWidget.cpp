//
// Created by ricardo on 2022/6/28.
//

#include "moc_BusWidget.cpp"

BusItem::BusItem(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap)
{

}

BusWidget::BusWidget()
{
    item = new BusItem(QPixmap(":/picture/bus.png"));
    animation = new QPropertyAnimation(item, "pos");

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

void BusWidget::ResetBusPos(PosPair *s, int num)
{
    // 先停止一下动画
    animation->stop();

    pos_pairs = s;
    pos = 0;
    node_num = num;

    item->setPos(pos_pairs[0].GetBusPosX(), pos_pairs[0].GetBusPosY());
}

void BusWidget::StartAnimation(int direction, int duration)
{
    bool is_animate = false;

    animation->setDuration(duration);
    animation->setStartValue(QPointF(pos_pairs[pos].GetBusPosX(), pos_pairs[pos].GetBusPosY()));

    switch (direction)
    {
        case BUS_CLOCK_WISE:
            pos++;
            is_animate = true;
            // 处理环绕一圈的情况
            if(pos == node_num)
            {
                pos = pos - node_num;
            }
            break;
        case BUS_COUNTER_CLOCK_WISE:
            pos--;
            is_animate = true;
            // 处理环绕一圈的情况
            if(pos == -1)
            {
                pos = pos + node_num;
            }
        default:
            break;
    }

    if(is_animate)
    {
        animation->setEndValue(QPointF(pos_pairs[pos].GetBusPosX(), pos_pairs[pos].GetBusPosY()));
        animation->start();
    }
}
