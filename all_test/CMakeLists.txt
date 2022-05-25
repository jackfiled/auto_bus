cmake_minimum_required(VERSION 3.0)
project(bus_all_test)

include_directories(../include)
include_directories(include)

aux_source_directory("../src/" SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" ALL_TEST_SRCS)

add_executable(bus_all_test ${SRCS} ${ALL_TEST_SRCS} main.c)

add_custom_command(TARGET bus_all_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/test_cases"
        "$<TARGET_FILE_DIR:bus_all_test>/test_cases")