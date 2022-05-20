//
// Created by ricardo on 2022/5/6.
//

#ifndef AUTO_PILOT_BUS_BUS_IO_H
#define AUTO_PILOT_BUS_BUS_IO_H
#include "rail.h"
#include "query.h"
#include "define.h"
#include "controller.h"
#include "string.h"
#include "stdio.h"

/**
 * 读取配置文件，创建轨道链表，同时读取需要使用的策略
 * @return 指向轨道链表的指针
 */
rail_node_t* ReadConfigFile();

/**
 * 读取标准输入流中的输入
 * @param inputString 输入的字符串
 * @return 当前读取的状态
 */
int ReadInput(char* inputString);

/**
 * 打印当前的状态
 * @param rails 轨道链表
 * @return 返回需输出的字符串
 */
char* PrintState();

#endif //AUTO_PILOT_BUS_BUS_IO_H
