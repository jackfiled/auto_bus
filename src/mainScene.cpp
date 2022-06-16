//
// Created by ricardo on 2022/6/11.
//

#include "mainScene.h"

void SceneManager::init()
{
    scene = new QGraphicsScene;
}

void SceneManager::initBusStop(rail_node_t *rail_head)
{
    pixmap_items = new QGraphicsPixmapItem[1];

    pixmap_items->setPixmap(QPixmap(":/picture/bus.png"));
    pixmap_items->setPos(100,100);

    scene->addItem(pixmap_items);
}

SceneManager::~SceneManager()
{
    delete []pixmap_items;
    delete scene;
}