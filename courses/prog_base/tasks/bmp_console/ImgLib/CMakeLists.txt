cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(ImgLib C)

set(SOURCES
  "ImgLib.c"
  )


include_directories("include")

add_library(${PROJECT_NAME} STATIC  ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

