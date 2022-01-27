#include <ndv/mat.h>
using namespace ndv;

#include <doctest/doctest.h>

TEST_CASE("Mat template class tests")
{
  Mat4 m = Mat4::diag(2);

  SUBCASE("Temp test")
  {
    CHECK(m[0][0] == 2);
  }
}
