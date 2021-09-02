file(GLOB_RECURSE ndvlib_SOURCES CONFIGURE_DEPENDS 
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
add_library(ndvlib ${ndvlib_SOURCES})

target_include_directories(ndvlib 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# fine-grained control of cxx standard
target_compile_features(ndvlib PUBLIC cxx_std_17)
set_target_properties(ndvlib PROPERTIES CXX_EXTENSIONS OFF)
