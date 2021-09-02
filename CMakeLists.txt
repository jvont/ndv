cmake_minimum_required(VERSION 3.11)
project(ndv VERSION 0.1
            DESCRIPTION "N-dimensional spatial vector templates"
            LANGUAGES CXX)

# enable BUILD_TESTING
include(CTest)

# include additional FindModule.cmake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# include FetchContent
# add MakeAvailable macro if <=3.14
include(FetchContent)
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(FetchContent_MakeAvailable)
endif()

add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE ndvlib)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# set compile features
target_compile_features(main PRIVATE cxx_std_17)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)