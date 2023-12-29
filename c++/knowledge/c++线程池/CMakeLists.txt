cmake_minimum_required(VERSION 3.16) # 设置最小cmake build version
project(
  multi_threaded
  VERSION 0.1
  LANGUAGES CXX) # 设置项目名称和版本

set(CMAKE_CXX_STANDARD 11) # 设置C++标准

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # 设置调试信息

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) # 添加头文件路径

aux_source_directory(./src SRC_LIST) # 添加源文件路径

add_executable(multi_threaded ${SRC_LIST}) # 生成可执行文件

target_link_libraries(multi_threaded pthread) # 链接pthread库
