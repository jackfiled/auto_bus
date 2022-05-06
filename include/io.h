//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_IO_H
#define AUTO_PILOT_BUS_IO_H
#include "rail.h"
#include "query.h"

enum read_state{
    /**
     * 时钟
     */
    clock = 0,
    /**
     * 读取中
     */
    reading,
    /**
     * 结束
     */
    end
};

/**
 * 读取输入的状态
 */
typedef enum read_state read_state_t;

/**
 * 读取配置文件，创建轨道链表，同时读取需要使用的策略
 * @return 指向轨道链表的指针
 */
rail_node_t* ReadConfigFile();

/**
 * 读取标准输入流中的输入
 * @param up_queries 上车的请求队列
 * @param down_queries 下车的请求队列
 * @return 当前读取的状态
 */
read_state_t ReadInput(up_bus_t* up_queries, down_bus_t* down_queries);

/**
 * 打印当前的状态
 * @param up_queries 上车的请求队列
 * @param down_queries 下车的请求队列
 * @param rails 轨道链表
 */
void PrintState(up_bus_t* up_queries, down_bus_t* down_queries, rail_node_t* rails);

#endif //AUTO_PILOT_BUS_IO_H
