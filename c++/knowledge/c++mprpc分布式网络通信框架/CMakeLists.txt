cmake_minimum_required(VERSION 3.16)
project(ocean_mprpc) # 设置项目名称

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) # 设置可执行文件输出路径

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib) # 设置项目库文件输出路径

include_directories(${PROJECT_SOURCE_DIR}/src) #设置项目编译头文件搜索路径

link_directories(${PROJECT_SOURCE_DIR}/lib) # 设置项目库文件搜索路径

# add_subdirectory(src)
add_subdirectory(example)