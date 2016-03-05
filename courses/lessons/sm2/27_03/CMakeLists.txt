cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(UnitTest C)

set(SOURCES
  "test.c"
  )


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} rt m pthread check)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

