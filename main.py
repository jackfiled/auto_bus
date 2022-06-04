import os

input_file = open("all.c", "w", encoding="utf-8")
include_path: str = "./include/"
src_path: str = "./src/"

# 写入需要用到的头文件
input_file.write(
    """#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUS_CLOCK_WISE 0 // 顺时针
#define BUS_COUNTER_CLOCK_WISE 1 // 逆时针
#define BUS_TARGET 2 // 目标
#define BUS_STOP 2 // 停止
#define BUS_TRUE 1 // 真
#define BUS_FAlSE 0 // 假
#define IO_CLOCK 0 // 读取时钟指令
#define IO_READING 1 // 读取请求指令
#define IO_END 2 // 读取结束指令
#define BUS_FCFS 0 // 先来先服务
#define BUS_SSTF 1 // 最短寻找时间优先
#define BUS_SCAN 2 // 顺便服务
    """
)

# 读取include, src两个文件夹
# include文件的顺序需要手动指定
include_list: list = ["rail.h", "query.h", "bus.h", "bus_io.h", "controller.h", "define.h"]
src_list: list = os.listdir(src_path)

for file_name in include_list:
    file_name = include_path + file_name
    with open(file_name, "r", encoding="utf-8") as include_file:
        while True:
            line: str = include_file.readline()
            if not line:
                break
            elif line[0] == "#":
                continue
            else:
                input_file.write(line)

for file_name in src_list:
    file_name = src_path + file_name
    with open(file_name, "r", encoding="utf-8") as src_file:
        while True:
            line: str = src_file.readline()
            if not line:
                break
            elif line[0] == "#":
                continue
            else:
                input_file.write(line)

with open("main.c", "r", encoding="utf-8") as main_file:
    while True:
        line: str = main_file.readline()
        if not line:
            break
        elif line[0] == "#":
            continue
        else:
            input_file.write(line)

input_file.close()
