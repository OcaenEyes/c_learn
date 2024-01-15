set(SRC_LIST userservice.cc ../user.pb.cc)

add_executable(callee ${SRC_LIST})
target_link_libraries(callee ocean_mprpc protobuf)
