add_compile_options(-fPIC)

message(${PROJECT_SOURCE_DIR}/thirds/muduo2.0.3/include)



find_library(MUDUONET muduo_net ${PROJECT_SOURCE_DIR}/thirds/muduo2.0.3/lib)
find_library(MUDUOBASE muduo_base ${PROJECT_SOURCE_DIR}/thirds/muduo2.0.3/lib)

message(${MUDUONET})
message(${MUDUOBASE})

aux_source_directory(. SRC_LIST)
add_library(ocean_mprpc SHARED ${SRC_LIST})
target_link_libraries(ocean_mprpc ${MUDUONET} ${MUDUOBASE} pthread zookeeper_mt)
