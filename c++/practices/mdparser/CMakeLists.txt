cmake_minimum_required(VERSION 3.4)
project(oceanmarkdown-core)

add_library(oceanmarkdowncore
    src/markdown.h
    src/markdown.cpp
)

target_include_directories(oceanmarkdowncore PUBLIC src)

add_executable(oceanmarkdown-core src/main.cpp)

target_link_libraries(oceanmarkdown-core PUBLIC oceanmarkdowncore)