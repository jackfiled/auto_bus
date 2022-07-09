//
// Created by ricardo on 2022/6/28.
//

#ifndef AUTO_BUS_GUI_BUS_WIDGET_H
#define AUTO_BUS_GUI_BUS_WIDGET_H
#include "QGraphicsPixmapItem"
#include "QTransform"
#include "QPropertyAnimation"

#include "PosPair.h"
#include "define.h"

/**
 * 显示公交车的对象
 * 继承了QObject QGraphicsPixmapItem
 * 用以使用qt的动画框架
 */
class BusItem: public QObject, public QGraphicsPixmapItem
{
    // 调用这个宏使其qt对象化
    Q_OBJECT
    // 注册了一个QPointF类型的变量pos
    // 读取这个变量通过 pos()函数
    // 写入这个变量通过 setPos()函数
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    explicit BusItem(const QPixmap& pixmap);
};

/**
 * 公交车显示动画控制类
 */
class BusWidget
{
public:
    /**
     * 真正的公交车显示对象
     */
    BusItem *item;

    explicit BusWidget();

    ~BusWidget();

    /**
     * 重置公交车
     * @param s 位置对数组的头指针
     * @param num 站点数目
     */
    void ResetBusPos(PosPair *s, int num);

    /**
     * 开始公交车动画
     * @param direction 动画的方向
     * @param duration 动画持续的时间 ms
     */
    void StartAnimation(int direction, int duration);

private:
    /**
     * 存储各个站点位置对的数组
     */
    PosPair *pos_pairs = nullptr;

    /**
     * 动画对象
     */
    QPropertyAnimation *animation;

    /**
     * 公交车所在的站点
     */
    int pos = 0;

    /**
     * 站点总数
     */
    int node_num = 0;
};


#endif //AUTO_BUS_GUI_BUS_WIDGET_H
