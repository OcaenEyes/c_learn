if(NOT ZeroMQ_ROOT)
  set(ZeroMQ_ROOT "$ENV{ZeroMQ_ROOT}")
endif()

if(NOT ZeroMQ_ROOT)
  find_path(_ZeroMQ_ROOT NAMES include/zmq.h)
else()
  set(_ZeroMQ_ROOT "${ZeroMQ_ROOT}")
endif()

find_path(
  ZeroMQ_INCLUDE_DIRS
  NAMES zmq.h
  HINTS ${_ZeroMQ_ROOT}/include)
# HINTS表示在默认搜索路径之前搜索

# 如果成功找到头文件，则将ZeroMQ_INCLUDE_DIRS设置为其位置。我们继续通过使用字符串操作和正则表达式，寻找相应版本的ZeroMQ库:
set(_ZeroMQ_H ${ZeroMQ_INCLUDE_DIRS}/zmq.h)
function(_zmqver_EXTRACT _ZeroMQ_VER_COMPONENT _ZeroMQ_VER_OUTPUT)
  set(CMAKE_MATCH_1 "0")
  set(_ZeroMQ_expr
      "^[ \\t]*#define[ \\t]+${_ZeroMQ_VER_COMPONENT}[ \\t]+([0-9]+)$")
  file(STRINGS "${_ZeroMQ_H}" _ZeroMQ_ver REGEX "${_ZeroMQ_expr}")
  string(REGEX MATCH "${_ZeroMQ_expr}" ZeroMQ_ver "${_ZeroMQ_ver}")
  set(${_ZeroMQ_VER_OUTPUT}
      "${CMAKE_MATCH_1}"
      PARENT_SCOPE)
endfunction()
_zmqver_extract("ZMQ_VERSION_MAJOR" ZeroMQ_VERSION_MAJOR)
_zmqver_extract("ZMQ_VERSION_MINOR" ZeroMQ_VERSION_MINOR)
_zmqver_extract("ZMQ_VERSION_PATCH" ZeroMQ_VERSION_PATCH)

# 然后，为find_package_handle_standard_args准备ZeroMQ_VERSION变量:
if(ZeroMQ_FIND_VERSION_COUNT GREATER 2)
  set(ZeroMQ_VERSION
      "${ZeroMQ_VERSION_MAJOR}.${ZeroMQ_VERSION_MINOR}.${ZeroMQ_VERSION_PATCH}")
else()
  set(ZeroMQ_VERSION "${ZeroMQ_VERSION_MAJOR}.${ZeroMQ_VERSION_MINOR}")
endif()

# 使用find_library命令搜索ZeroMQ库。因为库的命名有所不同，这里我们需要区分Unix的平台和Windows平台:

if(NOT ${CMAKE_C_PLATFORM_ID} STREQUAL "Windows")
  find_library(
    ZeroMQ_LIBRARIES
    NAMES zmq
    HINTS ${_ZeroMQ_ROOT}/lib ${_ZeroMQ_ROOT}/lib/x86_64-linux-gnu)
else()
  find_library(
    ZeroMQ_LIBRARIES
    NAMES
      libzmq
      "libzmq-mt-${ZeroMQ_VERSION_MAJOR}_${ZeroMQ_VERSION_MINOR}_${ZeroMQ_VERSION_PATCH}"
      "libzmq-${CMAKE_VS_PLATFORM_TOOLSET}-mt-${ZeroMQ_VERSION_MAJOR}_${ZeroMQ_VERSION_MINOR}_${ZeroMQ_VERSION_PATCH}"
      libzmq_d
      "libzmq-mt-gd-${ZeroMQ_VERSION_MAJOR}_${ZeroMQ_VERSION_MINOR}_${ZeroMQ_VERSION_PATCH}"
      "libzmq-${CMAKE_VS_PLATFORM_TOOLSET}-mt-gd-${ZeroMQ_VERSION_MAJOR}_${ZeroMQ_VERSION_MINOR}_${ZeroMQ_VERSION_PATCH}"
    HINTS ${_ZeroMQ_ROOT}/lib)
endif()

# 包含了标准FindPackageHandleStandardArgs.cmake，并调用相应的CMake命令。如果找到所有需要的变量，并且版本匹配，则将ZeroMQ_FOUND变量设置为TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  ZeroMQ
  FOUND_VAR ZeroMQ_FOUND
  REQUIRED_VARS ZeroMQ_INCLUDE_DIRS ZeroMQ_LIBRARIES
  VERSION_VAR ZeroMQ_VERSION)


# find-module通常遵循特定的模式:
    # 检查用户是否为所需的包提供了自定义位置。
    # 使用find_家族中的命令搜索所需包的必需组件，即头文件、库、可执行程序等等。我们使用find_path查找头文件的完整路径，并使用find_library查找库。CMake还提供find_file、find_program和find_package。这些命令的签名如下:
    # find_path(<VAR> NAMES name PATHS paths)
        # 如果搜索成功，<VAR>将保存搜索结果；如果搜索失败，则会设置为<VAR>-NOTFOUND。NAMES和PATHS分别是CMake应该查找的文件的名称和搜索应该指向的路径。
        # 初步搜索的结果中，可以提取版本号。示例中，ZeroMQ头文件包含库版本，可以使用字符串操作和正则表达式提取库版本信息。
        # 最后，调用find_package_handle_standard_args命令。处理find_package命令的REQUIRED、QUIET和版本参数，并设置ZeroMQ_FOUND变量。