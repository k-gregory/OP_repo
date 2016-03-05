cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(Module C)

set(SOURCES
  "src/main.c"
  "src/DoubleArray.c"
  )

add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

