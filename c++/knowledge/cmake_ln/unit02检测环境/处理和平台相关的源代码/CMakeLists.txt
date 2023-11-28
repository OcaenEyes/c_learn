cmake_minimum_required(VERSION 3.16)
project(learn05 LANGUAGES CXX)

add_executable(learn05 main.cpp)

# 定义以下目标编译定义，让预处理器知道系统名称
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(learn05 PUBLIC "IS_LINUX")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Drawin")
  target_compile_definitions(learn05 PUBLIC "IS_MACOS")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(learn05 PUBLIC "IS_WINDOWS")
endif()

# add_definitions会修改编译整个项目的定义
# target_compile_definitions将定义限制于一个特定的目标，以及通过PRIVATE|PUBLIC|INTERFACE限定符，限制这些定义可见性
# PRIVATE，编译定义将只应用于给定的目标，而不应用于相关的其他目标。 INTERFACE，对给定目标的编译定义将只应用于使用它的目标。
# PUBLIC，编译定义将应用于给定的目标和使用它的所有其他目标。
