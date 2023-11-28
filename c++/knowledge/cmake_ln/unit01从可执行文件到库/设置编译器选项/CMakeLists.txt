cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_COMPILER g++)

project(learn03)

message("C++ compiler flags: ${CMAKE_CXX_FLAGS}") # 打印当前编译器标志


list(APPEND flags "-fPIC" "-Wall") # 为目标添加标志列表
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

# fPIC ：fPIC的全称是 Position Independent Code， 用于生成位置无关代码
# 开启和关闭告警方法
    # 1、-w （小写）禁止所有警告消息。
    # 2、以“-W”(大写）开头开启特定的警告；
        # 例如：
            #-Wreturn-type(返回值告警),
            # -Wsign-compare（有符号和无符号对比告警）
            # -Wall (除extra外的所有告警)
            # -Wextra (all外的其他告警)
    # 3、以“-Wno-”开头关闭特定的警告;
        # 例如：
            # -Wno-return-type （取消返回值告警）
            # -Wno-sign-compare（取消有符号和无符号对比告警）

# 添加静态库geometry
add_library(geomtry STATIC geometry_circle.cpp geometry_circle.h)

target_compile_options(geomtry PRIVATE ${flags})

add_executable(learn03 main.cpp) # 生成可执行文件

# 为可执行目标设置编译选项
target_compile_options(learn03 PRIVATE "-fPIC")

# 可见性的含义如下:
    # PRIVATE，编译选项会应用于给定的目标，不会传递给与目标相关的目标
    # INTERFACE，给定的编译选项将只应用于指定目标，并传递给与目标相关的目标
    # PUBLIC，编译选项将应用于指定目标和使用它的目标。


target_link_libraries(learn03 geomtry) # 将静态库geometry，链接到可执行文件learn03
