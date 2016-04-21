cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Database C)

add_subdirectory(sqlite3)

set(SOURCES
  "src/main.c"
  )


include_directories("sqlite3")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sqlite3)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

