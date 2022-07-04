//
// Created by ricardo on 2022/6/11.
//

#include "mainScene.h"

SceneManager::SceneManager()
{
    scene = new QGraphicsScene;
    stop_node_number = 0;
    stop_node_distance = 0;
    pixmap_items = nullptr;
    stop_pos_pairs = nullptr;
    name_items = nullptr;
    pos_spots = nullptr;
    rail_path = nullptr;
    rect_item = new QGraphicsRectItem;
    bus = new BusWidget;

    // 画一个描边的矩形框
    rect_item->setRect(0, 0, 595, 395);
    scene->addItem(rect_item);
}

SceneManager::~SceneManager()
{
    delete []name_items;
    delete []pixmap_items;
    delete []stop_pos_pairs;
    delete []pos_spots;
    delete rail_path;
    delete bus;
    delete rect_item;
    delete scene;
}

void SceneManager::SetStopScene(int node_number, int node_distance)
{
    // 先清除屏幕
    ClearStopScene();

    stop_node_number = node_number;
    stop_node_distance = node_distance;

    pixmap_items = new QGraphicsPixmapItem[stop_node_number];
    stop_pos_pairs = new PosPair[stop_node_number];
    name_items = new QGraphicsSimpleTextItem[stop_node_number];
    pos_spots = new QGraphicsEllipseItem[stop_node_number * (node_distance - 1)];
    rail_path = new QGraphicsPathItem;

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

    // 初始化站点编号
    for(int i = 0; i < stop_node_number; i++)
    {
        name_items[i].setText(QString::number(i + 1));
        name_items[i].setPos(stop_pos_pairs[i].pos_x + 30, stop_pos_pairs[i].pos_y);

        scene->addItem(&name_items[i]);
    }

    // 设置画点的画笔
    QPen pen = QPen();
    pen.setWidth(2);
    pen.setColor(Qt::black);
    // 设置画轨道的画笔
    QPen rail_pen = QPen();
    rail_pen.setWidth(1);
    rail_pen.setColor(Qt::black);

    // 画轨道
    QPainterPath path;
    path.moveTo(PosPair::stop_begin_x, PosPair::stop_begin_y);

    // 画位置点
    int pos;
    for(int i = 0; i < stop_node_number; i++)
    {
        path.lineTo(stop_pos_pairs[i].pos_x, stop_pos_pairs[i].pos_y);

        // 处理在画最后一个点的时候数组越界的问题
        int next_id = i + 1;
        if(next_id == stop_node_number)
        {
            next_id = 0;
        }

        int x_distance = (stop_pos_pairs[next_id].pos_x - stop_pos_pairs[i].pos_x) / node_distance;
        int y_distance = (stop_pos_pairs[next_id].pos_y - stop_pos_pairs[i].pos_y) / node_distance;

        int spot_pos_x = stop_pos_pairs[i].pos_x;
        int spot_pos_y = stop_pos_pairs[i].pos_y;

        for(int j = 0; j < node_distance - 1; j++)
        {
            pos = i * (node_distance - 1) + j;

            spot_pos_x += x_distance;
            spot_pos_y += y_distance;

            pos_spots[pos].setPen(pen);
            pos_spots[pos].setBrush(QBrush(Qt::black));

            pos_spots[pos].setRect(spot_pos_x - 1, spot_pos_y - 1, 2, 2);

            scene->addItem(&pos_spots[pos]);
        }
    }

    // 最后在连回起点
    path.lineTo(PosPair::stop_begin_x, PosPair::stop_begin_y);
    rail_path->setPath(path);
    rail_path->setPen(rail_pen);
    scene->addItem(rail_path);

    // 设置公交车图像
    bus->ResetBusPos(stop_pos_pairs, node_number);
    scene->addItem(bus->item);
}

void SceneManager::ResetBus()
{
    bus->ResetBusPos(stop_pos_pairs, stop_node_number);
}

void SceneManager::ClearStopScene()
{
    // 从画布中移除所有的站点图片
    for(int i = 0; i < stop_node_number; i++)
    {
        scene->removeItem(&pixmap_items[i]);
    }

    // 移除站点编号
    for(int i = 0; i < stop_node_number; i++)
    {
        scene->removeItem(&name_items[i]);
    }

    // 移除位置点
    for(int i = 0; i < stop_node_number * (stop_node_distance - 1); i++)
    {
        scene->removeItem(&pos_spots[i]);
    }

    // 移除轨道
    if(rail_path != nullptr)
    {
        scene->removeItem(rail_path);
    }

    delete []name_items;
    delete []pixmap_items;
    delete []pos_spots;
    delete []stop_pos_pairs;
    delete rail_path;
}

void SceneManager::BeginBusAnimation(int direction, int duration)
{
    bus->StartAnimation(direction, duration);
}
