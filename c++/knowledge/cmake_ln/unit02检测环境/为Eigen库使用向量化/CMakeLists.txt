cmake_minimum_required(VERSION 3.16)
project(learn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11) # 声明为C++11项目
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CXX_STANDARD会设置我们想要的标准。 CXX_EXTENSIONS告诉CMake，只启用 ISO C++
# 标准的编译器标志，而不使用特定编译器的扩展。
# CXX_STANDARD_REQUIRED指定所选标准的版本。如果这个版本不可用，CMake将停止配置并出现错误。 当这个属性被设置为 OFF
# 时，CMake将寻找下一个标准的最新版本，直到一个合适的标志，这意味着，首先查找 C++ 20，然后是C++17，然后是C++14，然后是C++11
# ，然后是 C++98 。

find_package(Eigen3 3.3 REQUIRED CONFIG) # 使用eigen3库

include(CheckCXXCompilerFlag) # CheckCXXCompilerFlag.cmake 标准模块文件

check_cxx_compiler_flag("-march=native" _march_native_works
)# 检查-march=native编译器标志是否工作
check_cxx_compiler_flag("-xHost" _xhost_works) # -xHost编译器标志也开启:

set(_CXX_FLAGS)
if(_march_native_works)
  set(_CXX_FLAGS "-march=native")
elseif(_xhost_works)
  set(_CXX_FLAGS "-xHost")
else()
  message(STATUS "no suitable compiler flag found for vectorization")
endif()

add_executable(learn-no-optimized main.cpp) # 未优化版本
target_link_libraries(learn-no-optimized PRIVATE Eigen3::Eigen)

add_executable(learn main.cpp) # 优化版本
target_compile_options(learn PRIVATE ${_CXX_FLAGS})
target_link_libraries(learn PRIVATE Eigen3::Eigen)
