cmake_minimum_required(VERSION 3.14)
project(ndv VERSION 0.1
            DESCRIPTION "N-dimensional spatial vector templates"
            LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
endif()

add_subdirectory(src)

# run tests if this is the main project
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) OR BUILD_TESTING)
  message("tests!")
  add_subdirectory(tests)
endif()