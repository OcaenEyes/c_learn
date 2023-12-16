cmake_minimum_required(VERSION 3.16) # 配置cmake最小版本
project(oceanim_client) # 项目名字

# 配置头文件搜索路径
include_directories(
  # /workspaces/c_learn/c++/oceanim/v0.2/3rds/muduo2.0.3/include
  ${PROJECT_SOURCE_DIR}/../../3rds/muduo2.0.3/include)
# message(/workspaces/c_learn/c++/oceanim/v0.2/3rds/muduo2.0.3/include)

# 查找第三方库
find_library(
  MUDUONET muduo_net
  # /workspaces/c_learn/c++/oceanim/v0.2/3rds/muduo2.0.3/lib
  ${PROJECT_SOURCE_DIR}/../../3rds/muduo2.0.3/lib)
find_library(
  MUDUOBASE muduo_base
  # /workspaces/c_learn/c++/oceanim/v0.2/3rds/muduo2.0.3/lib
  ${PROJECT_SOURCE_DIR}/../../3rds/muduo2.0.3/lib)

aux_source_directory(. SRC_LIST) # 把.指定路径下的所有源文件名字放入变量名SRC_LIST里

add_executable(oceanim_client ${SRC_LIST})

# 链接库
target_link_libraries(oceanim_client ${MUDUONET} ${MUDUOBASE} pthread)
