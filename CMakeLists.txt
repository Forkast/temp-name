cmake_minimum_required(VERSION 3.9)

project(temp-name)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(temp-name src/main.c)
target_link_libraries(temp-name ${SDL2_LIBRARIES})
