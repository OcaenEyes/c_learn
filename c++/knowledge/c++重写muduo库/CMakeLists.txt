cmake_minimum_required(VERSION 3.16) # 指定CMake的最低版本要求

project(ocean_muduo) # 设置项目名称

set(CMAKE_CXX_STANDARD 11) # 设置C++标准

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # 设置编译选项

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib) # 设置库文件的输出路径

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include) # 添加头文件搜索路径

aux_source_directory(./src SRC_DIR) # 查找当前目录下的所有源文件

add_library(ocean_muduo SHARED ${SRC_DIR}) # 生成动态库

add_library(ocean_muduo_static STATIC ${SRC_DIR}) # 生成静态库

set_target_properties(ocean_muduo_static PROPERTIES OUTPUT_NAME "ocean_muduo"
)# 设置静态库输出名称

target_link_libraries(ocean_muduo pthread) # 添加链接库

# add_executable(ocean_muduo_prj ${SRC_DIR})

# target_link_libraries(ocean_muduo_prj pthread) # 添加链接库