cmake_minimum_required(VERSION 3.16)
project(test_ocean_muduo)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# ocean_muduo头文件
include_directories(${PROJECT_SOURCE_DIR}/../output/ocean_muduo/include)
# ocean_muduo库文件
find_library(OCEANMUDUEO ocean_muduo
             ${PROJECT_SOURCE_DIR}/../output/ocean_muduo/lib)

add_executable(test_ocean_muduo main.cpp)
target_link_libraries(test_ocean_muduo ${OCEANMUDUEO})
