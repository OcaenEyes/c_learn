PROJECT(message)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_libraries(/usr/local/lib)

add_executable(publish  ${CMAKE_CURRENT_SOURCE_DIR}/src/publish_run.cpp   ${CMAKE_CURRENT_SOURCE_DIR}/src/publisher.cpp)
target_link_libraries(publish	pthread)
target_link_libraries(publish	event)
target_link_libraries(publish	hiredis)

add_executable(subscribe  ${CMAKE_CURRENT_SOURCE_DIR}/src/subscribe_run.cpp   ${CMAKE_CURRENT_SOURCE_DIR}/src/subscriber.cpp)
target_link_libraries(subscribe	pthread)
target_link_libraries(subscribe	event)
target_link_libraries(subscribe	hiredis)