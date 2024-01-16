# set(SRC_LIST userservice.cc ../user.pb.cc ../rescode.pb.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc ../rescode.pb.cc)

add_executable(callee ${SRC_LIST})
target_link_libraries(callee ocean_mprpc protobuf)
