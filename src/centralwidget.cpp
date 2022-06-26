//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CentralWidget.h" resolved

#include "header/moc_centralwidget.cpp"
#include "form/ui_CentralWidget.h"


CentralWidget::CentralWidget(QWidget *parent, BusControllerModel *bus_controller) : QWidget(parent), ui(new Ui::CentralWidget)
{
    ui->setupUi(this);
    scene_manager = new SceneManager(20);

    ui->main_canva->setScene(scene_manager->scene);

    controller = bus_controller;

    SetControlConnection();
    SetWidgetConnection();
    SetupQueryList();
}

CentralWidget::~CentralWidget()
{
    DeleteQueryList();

    delete scene_manager;
    delete ui;
}

void CentralWidget::SetControlConnection()
{

}

void CentralWidget::SetWidgetConnection()
{
    QObject::connect(ui->create_query_button, &QPushButton::clicked,
                     this, &CentralWidget::AddQueryButtonClicked);
}

void CentralWidget::SetupQueryList()
{
    // 设置请求列表的表头
    QueryListItem *column_name = new QueryListItem(1,1);
    column_name->SetColumnName();

    query_items.push_back(column_name);

    // 在列表中显示
    QListWidgetItem *widget_item = new QListWidgetItem;
    ui->query_list->addItem(widget_item);
    ui->query_list->setItemWidget(widget_item, column_name);
}

void CentralWidget::DeleteQueryList()
{
    for(auto itor = query_items.begin(); itor != query_items.end(); ++itor)
    {
        delete *itor;
    }
    query_items.clear();
}

void CentralWidget::AppendQueryItem(int query_type, int node_id)
{
    QueryListItem *item = new QueryListItem(query_type, node_id);

    query_items.push_back(item);

    // 在列表中显示
    QListWidgetItem *widget_item = new QListWidgetItem;
    ui->query_list->addItem(widget_item);
    ui->query_list->setItemWidget(widget_item, item);
}

void CentralWidget::DeleteQueryItem(int query_id)
{
    // 由于表头的存在，且请求的编号从1开始，请求的编号恰好就是请求在列表中的位置
    QListWidgetItem *deleted_widget = ui->query_list->takeItem(query_id);

    auto itor = query_items.begin();

    for(int i = 0; i < query_id; i++)
    {
        ++itor;
    }

    delete deleted_widget;
    delete *itor;
    query_items.erase(itor);
}

void CentralWidget::AddQueryButtonClicked()
{

}