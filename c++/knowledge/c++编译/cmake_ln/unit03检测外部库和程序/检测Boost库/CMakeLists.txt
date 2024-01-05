cmake_minimum_required(VERSION 3.16)
project(learn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.71 REQUIRED COMPONENTS filesystem)
# 使用find_package搜索Boost。若需要对Boost强制性依赖，需要一个参数。这个例子中，此处加入文件系统，作为参数传递给find_package

# 添加可执行目标文件
add_executable(learn path-info.cpp)

# 将Boost库组件链接到 可执行目标
target_link_libraries(learn PUBLIC Boost::filesystem)