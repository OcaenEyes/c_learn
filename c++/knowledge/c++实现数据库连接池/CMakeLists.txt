cmake_minimum_required(VERSION 3.16) # 配置cmake最小版本
project(mysqlpool VERSION 0.1.0) # 配置项目名称和版本号

set(CMAKE_CXX_STANDARD 11) # 设置C++标准

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # 设置调试信息 

# set(CMAKE_BUILD_TYPE "Debug") # 设置编译类型为Debug
# set(CMAKE_BUILD_TYPE "Release") # 设置编译类型为Release

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) # 设置可执行文件的输出路径

include_directories(${PROJECT_SOURCE_DIR}/include) # 添加头文件搜索路径

aux_source_directory(./src SRC_LIST) # 设置源文件搜索路径

configure_file(${PROJECT_SOURCE_DIR}/conf/config.ini ${EXECUTABLE_OUTPUT_PATH}/conf/config.ini COPYONLY) # 复制配置文件到输出路径

add_executable(mysqlpool ${SRC_LIST}) # 生成可执行文件mysqlpool

target_link_libraries(mysqlpool mysqlclient pthread) # 链接mysqlclient库
