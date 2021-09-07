cmake_minimum_required(VERSION 3.11)
project(ndv VERSION 0.1
            DESCRIPTION "N-dimensional spatial vector templates"
            LANGUAGES CXX)

# file(GLOB_RECURSE ndv_SOURCES CONFIGURE_DEPENDS 
#   *.cpp
# )
# add_library(ndv ${ndv_SOURCES})

# target_include_directories(ndv
#   PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
# )

add_library(ndv INTERFACE)

target_include_directories(ndv
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# fine-grained control of cxx standard
target_compile_features(ndv INTERFACE cxx_std_17)
set_target_properties(ndv PROPERTIES CXX_EXTENSIONS OFF)
