//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_BUS_MODEL_H
#define AUTO_BUS_GUI_BUS_MODEL_H

#include "railsModel.h"
#include "queryModel.h"
#include "define.h"

#include "cstdio"
#include "string"
#include "sstream"
#include "QObject"

/**
 * 控制公交车的类，继承了QObject
 */
class BusControllerModel : public QObject
{
    Q_OBJECT
public:
    /**
     * 指向公交车所在站点的指针
     */
    rail_node_t *rail_pos;

    /**
     * 当前行进的距离
     */
    int distance;

    /**
     * 当前前进的方向
     */
    int direction;

    /**
     * 公交车的计时时刻
     */
    int bus_time;

    /**
     * 轨道对象
     */
    RailsModel *rail_manager;

    /**
     * 请求控制对象
     */
    QueryModel *query_manager;

    /**
     * 选定的策略
     */
    int chosen_strategy = -1;

    /**
     * 构造函数
     *
     */
    BusControllerModel();

    /**
     * 析构函数
     */
    ~BusControllerModel();

    std::string PrintState();
    bool JudgeOnStation();

public slots:
    /**
     * 处理打开配置文件信号的槽函数
     * @param file_name 配置文件名称
     */
    void ReadConfigFileSlot(const QString& file_name);



private:
    /**
     * 轨道的总长度
     */
    int total_distance = 10;

    /**
     * 获得公交车当前所在的位置
     * @return 公交车当前所在的位置
     */
    int GetBusPosition() const;

    /**
     * 读取指定的配置文件
     * @param file_name 提供的配置文件路径
     */
    void ReadConfigFile(const std::string& file_name);

    /**
     * 给出在指定的方向下，指定的请求于公交车当前位置的距离
     * @param query 指定的请求
     * @param orientation 指定的方向 BUS_CLOCK_WISE BUS_COUNTER_CLOCK_WISE
     * @return 距离
     */
    int GetQueryDistance(bus_query_t *query, int orientation) const;

    /**
     * 在先来先服务策略下应该前进的方向
     * @return 前进的方向
     */
    int FCFSDirection() const;

    /**
     * 在先来先服务策略下给出处理的请求
     * @return 需要处理的请求
     */
    bus_query_t *FCFSQuery() const;

    /**
     * 获得在SSTF策略下应该处理的请求
     * @return 指向需要处理的请求的指针
     */
    bus_query_t *SSTFGetQuery();

    /**
     * 根据指定的请求获得前进的方向，也就是前往指定的请求最近的方向
     * 在SSTF策略中使用
     * @param query 指定完成的请求
     * @return 前进的方向
     */
    int SSTFDirection(bus_query_t* query);

    /**
     * 在当前站上可以顺便服务的请求
     * @return 服务的请求指针
     */
    bus_query_t *SSTFBTWQuery() const;

    /**
     * 获得在SCAN策略下应该处理的请求
     * @return 指向需要处理的请求的指针
     */
    bus_query_t *SCANGetQuery();

    /**
     * 根据指定的请求获得前进的方向
     * 在SCAN策略中使用
     * @param query 指定完成的请求
     * @return 前进的方向
     */
    int SCANDirection(bus_query_t *query);

    /**
     * 在当前站上可以顺便服务的请求
     * @return 服务的请求指针
     */
    bus_query_t *SCANBTWQuery() const;
};

#endif //AUTO_BUS_GUI_BUS_MODEL_H
