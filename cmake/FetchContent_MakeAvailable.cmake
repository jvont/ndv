# from: https://gitlab.com/CLIUtils/modern-cmake/-/tree/master/examples/extended-project
# add FetchContent_MakeAvailable for CMake Versions <=3.14
macro(FetchContent_MakeAvailable NAME)
  FetchContent_GetProperties(${NAME})
  if(NOT ${NAME}_POPULATED)
    FetchContent_Populate(${NAME})
    add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
  endif()
endmacro()
