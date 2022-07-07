cmake_minimum_required(VERSION 3.10)
project(auto_bus_gui)

file(GLOB_RECURSE QRC_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.qrc)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QRC_SOURCE_FILES Resources.qrc)

set(CMAKE_PREFIX_PATH  "C:/Users/ricardo.DESKTOP-N6OVBK5/Programs/Qt/6.1.3/msvc2019_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

qt6_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src/header
)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_executable(auto_bus_gui main.cpp ${SRCS} ${QRC_FILES})
else()
    add_executable(auto_bus_gui WIN32 main.cpp ${SRCS} ${QRC_FILES})
endif ()

target_link_libraries(auto_bus_gui
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
