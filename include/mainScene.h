//
// Created by ricardo on 2022/6/11.
//

#ifndef AUTO_BUS_GUI_MAIN_SCENE_H
#define AUTO_BUS_GUI_MAIN_SCENE_H

#include "QGraphicsScene"
#include "QGraphicsPixmapItem"

class PosPair{

public:
    int pos_x;
    int pos_y;

    PosPair();
    /**
     * 获取两个站点之间的距离
     * @param stop_number 站点的数量
     * @return 站点之间的距离
     */
    int GetStopSpaceLength(int stop_number) const;
    /**
     * 加上一定的距离
     * @param length 需要加上的距离
     */
    void AddLength(int length);

private:
    const int stop_begin_x = 100;
    const int stop_begin_y = 80;
    const int stop_rail_width = 300;
    const int stop_rail_height = 200;

    int distance = 0;
};

class SceneManager
{
public:
    QGraphicsScene *scene;

    /**
     * 构造函数，同时生成站点
     * @param stop_node_number 站点的数量
     */
    explicit SceneManager(int stop_node_number);
    ~SceneManager();

private:
    /**
     * 显示站点的像素图对象
     */
    QGraphicsPixmapItem *pixmap_items;
    /**
     * 每个站点的所在位置
     */
    PosPair *stop_pos_pairs;

    QGraphicsRectItem *rect_item;
};

#endif //AUTO_BUS_GUI_MAIN_SCENE_H
