cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(data_formats C)

find_package(libxml2 REQUIRED)

set(SOURCES
  "src/main.c"
  "src/Driver.c"
  )


include_directories(${LIBXML2_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBXML2_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)
