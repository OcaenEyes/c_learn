cmake_minimum_required(VERSION 3.16) # 设置最小cmake build version
project(
  multi_threaded
  VERSION 0.1
  LANGUAGES CXX) # 设置项目名称和版本

set(CMAKE_CXX_STANDARD 11) # 设置C++标准

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # 设置调试信息

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output/lib) # 设置库文件的输出路径


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) # 添加头文件路径

aux_source_directory(./src SRC_LIST) # 添加源文件路径


file(COPY ./include/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output/include/)
add_library(threadpool STATIC ./src/threadpool.cpp) # 生成静态库
add_library(threadpooll SHARED ./src/threadpool.cpp) # 生成动态库


add_executable(multi_threaded ${SRC_LIST}) # 生成可执行文件

target_link_libraries(multi_threaded pthread threadpool) # 链接pthread库
