//
// Created by ricardo on 2022/6/27.
//

#include "moc_BusStrategyBase.cpp"

BusStrategyBase::BusStrategyBase()
{
    rails_model = new RailsModel;
    query_model = new QueryModel;
    bus_model = new BusModel;

    bus_tick = 0;
}

BusStrategyBase::~BusStrategyBase()
{
    delete rails_model;
    delete query_model;
    delete bus_model;
}

void BusStrategyBase::SetConnection() const
{

}

void BusStrategyBase::AppendQuerySlot(int query_type, int node_id) const
{
    rail_node_t *node = rails_model->FindNode(node_id);
    query_model->CreateQuery(query_type, node);
}

void BusStrategyBase::OneTickSlot(int remaining_time)
{
    // 时间流动
    bus_tick++;

    // 打印状态
    QString str = PrintState(remaining_time);
    emit PrintStateSignal(str);
}

void BusStrategyBase::BusBeginSlot()
{
    status = BUS_RUNNING;

    // 在一开始先打印一下状态
    QString str = PrintState(0);
    emit PrintStateSignal(str);
}

void BusStrategyBase::BusEndSlot()
{
    status = BUS_END;
    bus_tick = 0;

    bus_model->ResetBus(rails_model->rails);
}

QString BusStrategyBase::PrintState(int remaining_time) const
{
    int count = 0;
    rail_node_t *node = rails_model->rails;
    char target[25], clockwise[25], counterclockwise[25];

    if(node == nullptr)
    {
        return QString("No rails");
    }

    do
    {
        target[count] = '0';
        clockwise[count] = '0';
        counterclockwise[count] = '0';
        node = node->next_node;
        count++;
    } while (node != rails_model->rails);

    // 字符串末尾填0
    target[count] = '\0';
    clockwise[count] = '\0';
    counterclockwise[count] = '\0';

    bus_query_t *query = query_model->queries;
    int pos;

    while (query != nullptr)
    {
        pos = query->node->id - 1;

        if(query->type == BUS_CLOCK_WISE)
        {
            clockwise[pos] = '1';
        }
        else if (query->type == BUS_COUNTER_CLOCK_WISE)
        {
            counterclockwise[pos] = '1';
        }
        else
        {
            target[pos] = '1';
        }

        query = query->next_node;
    }

    QString str = QString::asprintf("Time:%d\n", bus_tick);
    str += "BUS:\n";
    str += QString::asprintf("position:%lf\n", bus_model->GetBusPosition(remaining_time));
    str = str + "target:" + target + "\n";
    str += "STATION:\n";
    str = str + "clockwise" + clockwise + "\n";
    str = str + "counterclockwise" + counterclockwise + "\n";

    return str;
}