//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CentralWidget.h" resolved

#include "header/moc_centralwidget.cpp"
#include "form/ui_CentralWidget.h"
#include "centralwidget.h"


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CentralWidget)
{
    ui->setupUi(this);
    scene_manager = new SceneManager(20);

    ui->main_canva->setScene(scene_manager->scene);
}

CentralWidget::~CentralWidget()
{
    delete scene_manager;
    delete ui;
}
