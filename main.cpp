#include <ndv/vec.h>
#include <ndv/mat.h>
using namespace bones;

#include <iostream>

int main()
{
  // Vec2f v1({1.2f, 3.1f});
  // Vec2f v2({2.2f, 1.1f});

  // Vec2f v = v1 + v2;

  // Mat<2, 2, float> m({{0, 1},{2, 3}});

  Mat<2, 2, float> m({0, 1, 2, 3});

  Vec<2, float> v = Vec2f::zero;

  return 0;
}