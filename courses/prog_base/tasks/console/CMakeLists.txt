cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(ConsoleColors C)

find_package(Curses REQUIRED)

set(SOURCES
  "main.c"
  )


include_directories(${CURSES_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

