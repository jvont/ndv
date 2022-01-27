#include <ndv/quat.h>
using namespace ndv;

#include <doctest/doctest.h>

TEST_CASE("Mat template class tests")
{
  Quat q = Quat::identity;

  SUBCASE("Temp test")
  {
    CHECK(q[0] == 1);
    CHECK(q[1] == 0);
  }
}
