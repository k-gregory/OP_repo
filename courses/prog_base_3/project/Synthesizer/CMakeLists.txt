cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
include(FindPkgConfig)

project(Synthesizer CXX)

pkg_search_module(SDL2 REQUIRED sdl2)

set(SOURCES
    "src/main.cpp"
    "src/application.cpp"
    "src/audiogenerator.cpp"
    )

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} m)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
