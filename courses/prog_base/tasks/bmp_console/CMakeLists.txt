cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(ConsoleBMP C)

add_subdirectory(ImgLib)

find_package(Curses REQUIRED)

set(SOURCES
  "main.c"
  )


include_directories(${CURSES_INCLUDE_DIR} "ImgLib/include")
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} ImgLib  m)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

