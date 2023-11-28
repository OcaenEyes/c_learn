cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_COMPILER g++) # 写在第二行，设置编译器为g++;  或者在 使用CLI中的-D选项，例如：cmake -D CMAKE_CXX_COMPILER=clang++ ..

project(learn02)

add_library(message STATIC message.h message.cpp) # 编译静态库

add_executable(learn02 main.cpp) # 编译可执行文件目标

target_link_libraries(learn02 message) # 将目标库链接到可执行目标


## STATIC：用于创建静态库，即编译文件的打包存档，以便在链接其他目标时使用
## SHARED：用于创建动态库，即可以动态链接，并在运行时加载的库
## OBJECT：可将给定add_library的列表中的源码编译到目标文件，不将它们归档到静态库中，也不能将它们链接到共享对象中。如果需要一次性创建静态库和动态库，那么使用对象库尤其有用
## MODULE：又为DSO组。与SHARED库不同，它们不链接到项目中的任何目标，不过可以进行动态加载。该参数可以用于构建运行时插件。



# option(USE_LIBRARY "Compile sources into a library" OFF)
    # 然后可通过CMake的-D CLI选项，例如【cmake -D USE_LIBRARY=ON ..】来设置USE_LIBRARY变量
    # option可接受三个参数：option(<option_variable> "help string" [initial value])
        # <option_variable>表示该选项的变量的名称。
        # "help string"记录选项的字符串，在CMake的终端或图形用户界面中可见。
        # [initial value]选项的默认值，可以是ON或OFF。

# 切换构建类型，例如：cmake -D CMAKE_BUILD_TYPE=Debug .. 
    # Debug：用于在没有优化的情况下，使用带有调试符号构建库或可执行文件。
    # Release：用于构建的优化的库或可执行文件，不包含调试符号。
    # RelWithDebInfo：用于构建较少的优化库或可执行文件，包含调试符号。
    # MinSizeRel：用于不增加目标代码大小的优化方式，来构建库或可执行文件
