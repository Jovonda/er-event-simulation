cmake_minimum_required(VERSION 3.10)
project(er_sim)

set(CMAKE_C_STANDARD 17)

set(SOURCE_FILES simlib.c er_sim.c)
add_executable(er_sim ${SOURCE_FILES})

target_link_libraries(er_sim PRIVATE m)