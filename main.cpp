#include <ndv/vec.h>
// #include <ndv/mat.h>
#include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{
  // Mat<3, 3, float> m;

  Quat<float> q(0);

  Vec<2, float> v1(4, 8);
  Vec<2, float> v2(-8, 4);

  float r = angle(v1, v2);

  return 0;
}