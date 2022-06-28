//
// Created by ricardo on 2022/6/11.
//

#ifndef AUTO_BUS_GUI_MAIN_SCENE_H
#define AUTO_BUS_GUI_MAIN_SCENE_H

#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "QGraphicsSimpleTextItem"

#include "PosPair.h"
#include "BusWidget.h"

class SceneManager
{
public:
    QGraphicsScene *scene;

    /**
     * 构造函数，同时生成站点
     */
    explicit SceneManager();
    ~SceneManager();

    /**
     * 生成站点画面
     * @param node_number
     */
    void SetStopScene(int node_number);

    /**
     * 开始公交车动画
     * @param direction 公交车前进的方向
     * @param duration 前进持续的时间
     */
    void BeginBusAnimation(int direction, int duration);

private:
    /**
     * 显示站点的像素图对象
     */
    QGraphicsPixmapItem *pixmap_items;

    QGraphicsSimpleTextItem *name_items;

    /**
     * 每个站点的所在位置
     */
    PosPair *stop_pos_pairs;

    /**
     * 公交车对象
     */
    BusWidget *bus;

    /**
     * 总共的站点数量
     */
    int stop_node_number;

    /**
     * 一个矩形的边框
     * 使无论中间存在多少站点，这个scene都能在view的中心
     */
    QGraphicsRectItem *rect_item;

    /**
     * 清除画面
     */
    void ClearStopScene();
};

#endif //AUTO_BUS_GUI_MAIN_SCENE_H
