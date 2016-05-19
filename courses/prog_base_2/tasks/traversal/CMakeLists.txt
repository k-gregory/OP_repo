cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
include(FindPkgConfig)

project(traversal C)

pkg_search_module(JSON REQUIRED json-c)

set(SOURCES
    "src/main.c"
    )

include_directories(${JSON_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${JSON_LIBRARIES} m)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)
