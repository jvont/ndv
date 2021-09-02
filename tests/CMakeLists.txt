# use doctest for testing
FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/onqtam/doctest"
  GIT_TAG "2.4.6"
)
FetchContent_MakeAvailable(doctest)

file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS *.cpp *.h *.hpp)
add_executable(tests ${TESTS_SOURCES})

target_link_libraries(tests PRIVATE doctest::doctest ndvlib)

# set compile features
target_compile_features(tests PRIVATE cxx_std_17)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)

# add doctest tests to CTest
include(doctest)
doctest_discover_tests(tests)
