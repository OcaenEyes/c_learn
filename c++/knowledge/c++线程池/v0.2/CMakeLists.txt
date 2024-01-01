cmake_minimum_required(VERSION 3.16)
project(threadpool CXX VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 设置动态库输出路径
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/lib)

# 设置源文件路径
aux_source_directory(. SRC_LIST)

# 生成动态库
add_library(threadpool SHARED threadpool.cpp)
# 安装头文件
# install(FILES threadpool.h DESTINATION include)


# 链接pthread库
target_link_libraries(threadpool pthread)


# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/bin)
# 生成测试可执行文件
add_executable(test_threadpool ${SRC_LIST})
# 链接动态库
target_link_libraries(test_threadpool threadpool)