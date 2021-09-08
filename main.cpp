#include <ndv/vec.h>
#include <ndv/mat.h>
#include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{
  // Mat4x4 m = look_at(Vec3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0));

  // Quat q = Quat::axis_angle(Vec3(1, 0, 0), 0.157f);

  // std::cout << q << std::endl;

  Mat4x4 m = Mat4x4({
    {8, 5000000.0f, 1, 0},
    {0, 2, 10000.0f, 0},
    {8, 0, 1, 303454.0f},
    {0.0001f, 0, 1, 1}
  });
  std::cout << m << std::endl;

  Vec<5, float> v({0.000001f, 1000000.0f, 0.0f, 4.4444f, 800000.0f});
  std::cout << v << std::endl;
  
  return 0;
}