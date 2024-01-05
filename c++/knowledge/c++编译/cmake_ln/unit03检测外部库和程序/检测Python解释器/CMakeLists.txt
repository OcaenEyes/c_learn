cmake_minimum_required(VERSION 3.16)
project(learn LANGUAGES CXX)

find_package(PythonInterp REQUIRED) # 使用find_package 命令找到python解释器

execute_process(
  COMMAND ${PYTHON_EXECUTABLE} "-c" "print('hello,gzy,python')"
  RESULT_VARIABLE _status
  OUTPUT_VARIABLE _learn
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "RESULT_VARIABLE is : ${_status}")
message(STATUS "OUTPUT_VARIABLE is : ${_learn}")

# find_package是用于发现和设置包的CMake模块的命令。这些模块包含CMake命令，用于标识系统标准位置中的包。
# CMake模块文件称为Find<name>.cmake，当调用find_package(<name>)时，模块中的命令将会运行。

# 软件包没有安装在标准位置时，CMake无法正确定位它们。用户可以使用CLI的-D参数传递相应的选项，告诉CMake查看特定的位置。
# Python解释器可以使用以下配置: cmake -D PYTHON_EXECUTABLE=/custom/location/python ..
