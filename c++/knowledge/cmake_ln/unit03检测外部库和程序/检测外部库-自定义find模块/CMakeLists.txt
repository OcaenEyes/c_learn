cmake_minimum_required(VERSION 3.16)
project(learn LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 将当前源目录CMAKE_CURRENT_SOURCE_DIR，添加到CMake将查找模块的路径列表CMAKE_MODULE_PATH中。
# 这样CMake就可以找到，我们自定义的FindZeroMQ.cmake模块:
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(ZeroMQ REQUIRED)

add_executable(server server.c)

target_include_directories(server PRIVATE ${ZeroMQ_INCLUDE_DIRS})
target_link_libraries(server PRIVATE ${ZeroMQ_LIBRARIES})
