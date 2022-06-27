//
// Created by ricardo on 2022/6/11.
//

#include "mainScene.h"

SceneManager::SceneManager()
{
    scene = new QGraphicsScene;
    stop_node_number = 0;
    pixmap_items = nullptr;
    stop_pos_pairs = nullptr;
    rect_item = new QGraphicsRectItem;

    // 画一个描边的矩形框
    rect_item->setRect(0, 0, 595, 395);
    scene->addItem(rect_item);
}

SceneManager::~SceneManager()
{
    ClearScene();
    delete scene;
}

void SceneManager::SetStopScene(int node_number)
{
    // 先清除屏幕
    ClearScene();

    stop_node_number = node_number;
    pixmap_items = new QGraphicsPixmapItem[stop_node_number];
    stop_pos_pairs = new PosPair[stop_node_number];

    int stop_space_length = stop_pos_pairs->GetStopSpaceLength(stop_node_number);
    double stop_scale = 0.15;
    QTransform stop_transform;

    stop_transform.scale(stop_scale, stop_scale);

    // 为站点对象设置
    // 并将其添加到画图中
    for(size_t i = 0; i < stop_node_number; i++)
    {
        pixmap_items[i].setPixmap(QPixmap(":/picture/stop.png"));
        pixmap_items[i].setTransform(stop_transform);
        scene->addItem(&pixmap_items[i]);
    }

    // 初始化站点的位置
    for(size_t i = 0; i < stop_node_number; i++)
    {
        // 对于后面的节点执行累加
        for(size_t j = i + 1; j < stop_node_number; j++)
        {
            stop_pos_pairs[j].AddLength(stop_space_length);
        }
        pixmap_items[i].setPos(stop_pos_pairs[i].pos_x, stop_pos_pairs[i].pos_y);
    }
}

void SceneManager::ClearScene()
{
    // 从画布中移除所有的站点图片
    for(int i = 0; i < stop_node_number; i++)
    {
        scene->removeItem(&pixmap_items[i]);
    }

    delete []pixmap_items;
    delete []stop_pos_pairs;
}

PosPair::PosPair()
{
    pos_x = stop_begin_x;
    pos_y = stop_begin_y;
}

int PosPair::GetStopSpaceLength(int stop_number) const
{
    return 2 * (stop_rail_width + stop_rail_height) / stop_number;
}

void PosPair::AddLength(int length)
{
    distance += length;

    if(distance > 2 * stop_rail_width + stop_rail_height)
    {
        // 站点在左轨道

        pos_x = stop_begin_x;
        pos_y = stop_begin_y + (stop_rail_width + stop_rail_height) * 2 - distance;
    }
    else if(distance > stop_rail_width + stop_rail_height and
        distance <= 2 * stop_rail_width + stop_rail_height)
    {
        // 站点在下轨道

        pos_y = stop_begin_y + stop_rail_height;
        pos_x = stop_begin_x + 2 * stop_rail_width + stop_rail_height - distance;
    }
    else if(distance > stop_rail_width and
        distance <= stop_rail_width + stop_rail_height)
    {
        // 站点在右轨道

        pos_x = stop_begin_x + stop_rail_width;
        pos_y = stop_begin_y + distance - stop_rail_width;
    }
    else
    {
        // 站点在上轨道

        pos_y = stop_begin_y;
        pos_x = stop_begin_x + distance;
    }
}

int PosPair::GetBusPosX() const
{
    int result;

    if(pos_x <= stop_begin_x)
    {
        result = stop_begin_x - stop_bus_distance;
    }
    else if(pos_x >= stop_begin_x + stop_rail_width)
    {
        result = pos_x + stop_bus_distance;
    }
    else
    {
        result = pos_x;
    }

    return result;
}

int PosPair::GetBusPosY() const
{
    int result;

    if(pos_y <= stop_begin_y)
    {
        result = stop_begin_y - stop_bus_distance;
    }
    else if(pos_y >= stop_begin_y + stop_rail_width)
    {
        result = pos_y + stop_bus_distance;
    }
    else
    {
        result = pos_y;
    }

    return result;
}
