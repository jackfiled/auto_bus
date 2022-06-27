//
// Created by ricardo on 2022/6/11.
//

#ifndef AUTO_BUS_GUI_MAIN_SCENE_H
#define AUTO_BUS_GUI_MAIN_SCENE_H

#include "QGraphicsScene"
#include "QGraphicsPixmapItem"

/**
 * 储存每个站点位置的类
 */
class PosPair{

public:
    /*
     * 站点位置的x坐标
     */
    int pos_x;
    /**
     * 站点位置的y坐标
     */
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

    /**
     * 获得该站点公交车停车的位置x坐标
     * @return
     */
    int GetBusPosX() const;

    /**
     * 获得该站点公交车停车位置的y坐标
     * @return
     */
    int GetBusPosY() const;

private:
    const int stop_begin_x = 100;
    const int stop_begin_y = 80;
    const int stop_rail_width = 300;
    const int stop_rail_height = 200;
    const int stop_bus_distance = 20;

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
    explicit SceneManager();
    ~SceneManager();

    /**
     * 生成站点画面
     * @param node_number
     */
    void SetStopScene(int node_number);

private:
    /**
     * 显示站点的像素图对象
     */
    QGraphicsPixmapItem *pixmap_items;
    /**
     * 每个站点的所在位置
     */
    PosPair *stop_pos_pairs;

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
    void ClearScene();
};

#endif //AUTO_BUS_GUI_MAIN_SCENE_H
