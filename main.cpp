#include <ndv/vec.h>
#include <ndv/mat.h>
// #include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{
  Mat4x4 m = look_at(Vec3(0, 0, 1), Vec3(0), Vec3(0, 1, 0));

  // Mat4x4 m1 = orthographic(800.0f, 400.0f, 1.0f, 10.0f);
  // Mat4x4 m2 = orthographic(800.0f, 400.0f, 1.0f, 10.0f);

  return 0;
}