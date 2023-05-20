cmake_minimum_required(VERSION 3.25)
project(simple_server C)

set(CMAKE_C_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(
        simple_server
        main.c
        http/request.c
        http/request.h
        http/message.c
        http/message.h
        utils/list.c
        utils/list.h
        utils/utils.h)

enable_testing()
add_subdirectory(test)