cmake_minimum_required(VERSION 3.11)
project(ndv VERSION 0.1
            DESCRIPTION "N-dimensional spatial vector templates"
            LANGUAGES CXX)

include(CTest)

add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE ndvlib)

# set compile features
target_compile_features(main PRIVATE cxx_std_17)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)