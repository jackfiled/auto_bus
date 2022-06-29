//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CentralWidget.h" resolved

#include "header/moc_centralwidget.cpp"
#include "form/ui_CentralWidget.h"


CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CentralWidget)
{
    ui->setupUi(this);
    scene_manager = new SceneManager;

    ui->main_canva->setScene(scene_manager->scene);

    SetWidgetConnection();
    SetupQueryList();
}

CentralWidget::~CentralWidget()
{
    DeleteQueryList();

    delete scene_manager;
    delete ui;
}

void CentralWidget::SetController(BusStrategyBase *c)
{
    controller = c;
    SetControlConnection();
    SetRailsScene(controller->rails_model->node_num);
}

void CentralWidget::SetStrategyLabel(int strategy)
{
    QString name;

    switch (strategy)
    {
        case BUS_FCFS:
            name = QString("先来先服务");
            break;
        case BUS_SSTF:
            name = QString("最短寻找时间");
            break;
        case BUS_SCAN:
            name = QString("顺便服务");
            break;
        default:
            break;
    }

    ui->strategy_label->setText(name);
}

void CentralWidget::ResetOutput()
{
    // 清除日志输出
    ui->text_output->clear();

    // 重设公交车位置
    scene_manager->ResetBus();

    // 删除请求列表的所有元素
    auto first_item = query_items.begin();
    int query_id = 1;
    first_item++;

    for(auto itor = first_item; itor != query_items.end(); itor++)
    {
        QListWidgetItem *deleted_item = ui->query_list->takeItem(query_id);

        delete deleted_item;
        delete *itor;
        query_id++;
    }

    // 保留第一个的表头指针
    QueryListItem *column_name = query_items.front();
    query_items.clear();
    query_items.push_back(column_name);
}

void CentralWidget::SetControlConnection()
{
    // 设置添加请求事件的连接
    QObject::connect(this, &CentralWidget::AppendQuerySignal,
                     controller, &BusStrategyBase::AppendQuerySlot);

    // 设置删除请求事件的连接
    QObject::connect(controller, &BusStrategyBase::DeleteQuerySignal,
                     this, &CentralWidget::DeleteQueryItemSlot);

    // 设置打印状态事件的连接
    QObject::connect(controller, &BusStrategyBase::PrintStateSignal,
                     this, &CentralWidget::PrintStateSlot);

    QObject::connect(controller, &BusStrategyBase::BusRunningSignal,
                     this, &CentralWidget::BeginBusAnimationSlot);

}

void CentralWidget::SetWidgetConnection()
{
    // 处理点击创建请求按钮事件
    QObject::connect(ui->create_query_button, &QPushButton::clicked,
                     this, &CentralWidget::AddQueryButtonClicked);

    // 处理添加请求事件
    QObject::connect(this, &CentralWidget::AppendQuerySignal,
                     this, &CentralWidget::AppendQueryItemSlot);
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

void CentralWidget::AppendQueryItemSlot(int query_type, int node_id)
{
    QueryListItem *item = new QueryListItem(query_type, node_id);

    query_items.push_back(item);

    // 在列表中显示
    QListWidgetItem *widget_item = new QListWidgetItem;
    ui->query_list->addItem(widget_item);
    ui->query_list->setItemWidget(widget_item, item);
}

void CentralWidget::DeleteQueryItemSlot(int query_type, int node_id)
{
    // 由于请求列表头的存在，编号从1开始
    int query_id = 1;

    // 先排除表头的影响
    auto first_item = query_items.begin();
    first_item++;

    for(auto itor = first_item; itor != query_items.end(); ++itor)
    {
        if((*itor)->query_type == query_type and (*itor)->target_node_id == node_id)
        {
            break;
        }
        query_id++;
    }

    QListWidgetItem *deleted_item = ui->query_list->takeItem(query_id);

    auto pos = query_items.begin();

    for(int i = 0; i < query_id; i++)
    {
        ++pos;
    }

    delete deleted_item;
    delete *pos;
    query_items.erase(pos);
}

void CentralWidget::PrintStateSlot(const QString& string)
{
    ui->text_output->insertPlainText(string);

    // 设置光标在最后一行
    QTextCursor cursor = ui->text_output->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->text_output->setTextCursor(cursor);
}

void CentralWidget::BeginBusAnimationSlot(int direction, int duration)
{
    scene_manager->BeginBusAnimation(direction, duration);
}

void CentralWidget::AddQueryButtonClicked()
{
    int query_type = ui->query_type_combo->currentIndex();
    int node_id = ui->query_node_combo->currentIndex() + 1;

    if(node_id == 0)
    {
        //此时还没有读取配置文件
        QMessageBox::warning(this, "警告", "请先读取配置文件");
        return;
    }

    emit AppendQuerySignal(query_type, node_id);
}

void CentralWidget::SetRailsScene(int node_num)
{
    scene_manager->SetStopScene(node_num);
    SetRailsComboBox(node_num);
}

void CentralWidget::SetRailsComboBox(int node_num)
{
    ui->query_node_combo->clear();

    for(int i = 1; i <= node_num; i++)
    {
        QString node_str = QString::asprintf("第%d站", i);
        ui->query_node_combo->addItem(node_str);
    }
}