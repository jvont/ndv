#include <ndv/vec.h>

#include <doctest/doctest.h>

TEST_CASE("Vec template class tests")
{
  Vec<2, int> v1;
  v1.values[0] = 2;
  v1.values[1] = 3;

  Vec<2, int> v2;
  v2.values[0] = 4;
  v2.values[1] = 5;
  
  int s = 6;

  SUBCASE("Vec<2, int> operator tests")
  {
    // Vec<2, int> r = v1;
    // r += v2;
    // check(r == Vec<2, int>)
  }
}
