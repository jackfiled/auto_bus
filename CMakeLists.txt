cmake_minimum_required(VERSION 3.10) # 设置cmake项目需要的cmake最小版本

add_subdirectory(third_party/GTest)
add_subdirectory(test)
add_subdirectory(all_test)

project(auto_pilot_bus) # 设置项目的名称

set(CMAKE_C_STANDARD 11) # 设置项目的C语言标准版本
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) # 设置项目的产生的库的路径，这里直接设为二进制文件处

# 设置项目的头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include/
)

aux_source_directory(./src SRC)

# 产生可执行文件
add_executable(bus main.c ${SRC})