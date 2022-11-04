cmake_minimum_required(VERSION 3.10)
project(base_station)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES simlib.c base_station.c)
add_executable(base_station ${SOURCE_FILES})

target_link_libraries(base_station PRIVATE m)