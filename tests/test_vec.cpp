#include <ndv/vec.h>
using namespace ndv;

#include <doctest/doctest.h>

TEST_CASE("Vec template class tests")
{
  Vec<2, int> v1;
  v1.x = 2;
  v1.y = 3;

  SUBCASE("Temp test")
  {
    CHECK(v1.x == 2);
  }
}
