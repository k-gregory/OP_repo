cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Lab4 C)

add_subdirectory(sqlite3)

find_package(Curses REQUIRED)

set(SOURCES
  "src/main.c"
  "src/DBUtil.h"
  "src/DBUtil.c"
  "src/DBQueries.h"
  "src/DBQueries.c"
  "src/types.h"
  )


include_directories("sqlite3")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sqlite3)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

