PROJECT(message)


link_libraries(/usr/local/lib)

add_executable(publish  ${CMAKE_CURRENT_SOURCE_DIR}/publish_run.cpp   ${CMAKE_CURRENT_SOURCE_DIR}/publisher.cpp)
target_link_libraries(publish	pthread)
target_link_libraries(publish	event)
target_link_libraries(publish	hiredis)

add_executable(subscribe  ${CMAKE_CURRENT_SOURCE_DIR}/subscribe_run.cpp   ${CMAKE_CURRENT_SOURCE_DIR}/subscriber.cpp)
target_link_libraries(subscribe	pthread)
target_link_libraries(subscribe	event)
target_link_libraries(subscribe	hiredis)