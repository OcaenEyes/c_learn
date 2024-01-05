cmake_minimum_required(VERSION 3.16)
project(learn LANGUAGES CXX)

# C++11支持，可用的Python解释器，以及Bash shell
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

# 定义库 及主要可执行文件的依赖关系，以及测试可执行文件
add_library(sum_integers sum_integers.cpp)

# main应用程序
add_executable(learn main.cpp)
target_link_libraries(learn sum_integers)

# test应用程序
add_executable(cpptest test.cpp)
target_link_libraries(cpptest sum_integers)


# 打开测试功能并定义四个测试。最后两个测试， 调用相同的Python脚本，先没有任何命令行参数，再使用--short
enable_testing()
add_test(
  NAME bashtest
  COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:learn>
  )
add_test(
  NAME cpptest
  COMMAND $<TARGET_FILE:cpptest>
  )
add_test(
  NAME python_test_long
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py --executable $<TARGET_FILE:learn>
  )
add_test(
  NAME python_test_short
  COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py --short --executable $<TARGET_FILE:learn>
  )