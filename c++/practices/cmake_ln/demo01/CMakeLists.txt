cmake_minimum_required(VERSION 3.0.0)
project(oc VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/include) #设置include

include(CTest)
enable_testing()

file(GLOB_RECURSE DEMOTEST_LIB_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(demotest STATIC ${DEMOTEST_LIB_SRC}) #编译静态库

add_executable(oc main.cpp) #添加文件
target_link_libraries(oc demotest) #添加静态库

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
