//
// Created by ricardo on 2022/6/11.
//

#ifndef AUTO_BUS_GUI_MAIN_SCENE_H
#define AUTO_BUS_GUI_MAIN_SCENE_H

#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "railsModel.h"

class SceneManager
{
public:
    QGraphicsScene *scene;

    ~SceneManager();

    /**
     * 初始化绘制场景
     */
    void init();

    /**
     * 初始化场景中的站点
     * @param rail_head 轨道的头节点
     */
    void initBusStop(rail_node_t *rail_head);

private:
    QGraphicsPixmapItem *pixmap_items;
};

#endif //AUTO_BUS_GUI_MAIN_SCENE_H
