#include <ndv/vec.h>
#include <ndv/mat.h>
// #include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{
  Mat4x4 m = look_at(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));
  
  return 0;
}