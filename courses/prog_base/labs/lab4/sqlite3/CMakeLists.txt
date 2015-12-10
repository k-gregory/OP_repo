cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(sqlite3 C)

set(SOURCES
  "sqlite3.c"
  )

add_library(${PROJECT_NAME} STATIC  ${SOURCES})
target_link_libraries(${PROJECT_NAME} pthread dl)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

