cmake_minimum_required(VERSION 4.1)
project(picture C)

set(CMAKE_C_STANDARD 11)

add_executable(picture main.c animation.c)

target_link_libraries(picture -lmingw32 -lalleg44)
