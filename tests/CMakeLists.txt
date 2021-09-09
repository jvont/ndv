# # include FetchContent
include(FetchContent)
include(FetchContent_MakeAvailable)

# use doctest for testing
FetchContent_Declare(
  doctest
  GIT_REPOSITORY "https://github.com/onqtam/doctest"
  GIT_TAG "2.4.6"
)
FetchContent_MakeAvailable(doctest)

file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS *.cpp *.h *.hpp)
add_executable(ndv-tests ${TESTS_SOURCES})

target_link_libraries(ndv-tests PRIVATE doctest::doctest ndv)

# set compile features
set_target_properties(ndv-tests PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

# add doctest tests to CTest
include(doctest)
doctest_discover_tests(ndv-tests)
