# set(SRC_LIST caller_userservice.cc ../user.pb.cc ../rescode.pb.cc)
set(SRC_LIST caller_friendservice.cc ../friend.pb.cc ../rescode.pb.cc)

add_executable(caller ${SRC_LIST})
target_link_libraries(caller ocean_mprpc protobuf)
