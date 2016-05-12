cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(Lab3 C)

set(TEST_SOURCES
  "tests.c"
  "am_queue.c"
  )

set(APP_SOURCES
  "am_queue.c"
  "am_observer.c"
  "main.c")

add_executable("${PROJECT_NAME}_tests" ${TEST_SOURCES})
add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_link_libraries("${PROJECT_NAME}_tests" check  m rt pthread subunit)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)
