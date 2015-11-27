cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(Lab3 C)

find_package(Curses REQUIRED)

set(SOURCES
  "main.c"
  "commands.c"
  )


include_directories(${CURSES_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} m)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

