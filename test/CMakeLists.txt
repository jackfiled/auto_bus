cmake_minimum_required(VERSION 3.0)
project(bus_test)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(./GTest)

include_directories(GTest/googletest/include)
include_directories(GTest/googlemock/include)
include_directories(../include)

aux_source_directory("../src/" SRCS)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" TEST_SRCS)

add_executable(bus_test ${SRCS} ${TEST_SRCS})

target_link_libraries(bus_test
        PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
        pthread
)
