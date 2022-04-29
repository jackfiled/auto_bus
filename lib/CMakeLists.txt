aux_source_directory(. LIB_SRCS)

include_directories(../include)

add_library(bus_lib ${LIB_SRCS})