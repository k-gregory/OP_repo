cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
include(FindPkgConfig)

project(Synthesizer C)

pkg_search_module(SDL2 REQUIRED sdl2)
link_directories(${SDL2_LIBRARY_DIRS})

set(SOURCES
    "src/main.c"
    "src/SimpleWaves.c"
    "src/audio_utils.c"
    )

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} m)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)
