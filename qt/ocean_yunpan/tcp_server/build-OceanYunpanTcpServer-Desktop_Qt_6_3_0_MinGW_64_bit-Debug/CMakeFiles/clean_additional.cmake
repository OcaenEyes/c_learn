# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OceanYunpanTcpServer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OceanYunpanTcpServer_autogen.dir\\ParseCache.txt"
  "OceanYunpanTcpServer_autogen"
  )
endif()
