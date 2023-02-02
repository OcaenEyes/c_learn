cmake_minimum_required(VERSION 3.4)
project(oceanmarkdown-core)

add_library(oceanmarkdowncore
    src/markdown.h
    src/markdown.cpp
    src/thirds/flowchart.js
    src/thirds/custom-mathjax.min.js
    src/thirds/a11y/assistive-mml.js
    src/thirds/raphael.js
)

target_include_directories(oceanmarkdowncore PUBLIC src)

add_executable(oceanmarkdown-core src/main.cpp)

target_link_libraries(oceanmarkdown-core PUBLIC oceanmarkdowncore)