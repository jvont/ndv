#include <ndv/vec.h>
#include <ndv/mat.h>
#include <ndv/quat.h>
using namespace ndv;

#include <iostream>

int main()
{
  Vec4 v({0.000001f, 1000000.0f, 0.0f, 800000.0f});
  std::cout << "Vec:  " << std::endl;
  std::cout << v << std::endl;

  Mat4x4 m = Mat4x4({
    {8, 5000000.0f, 1, 0},
    {0, 2, 10000.0f, 0},
    {8, 0, 1, 303454.0f},
    {0.0001f, 0, 1, 1}
  });
  std::cout << "Mat:" << std::endl;
  std::cout << m << std::endl;

  Quat q(1.0f, 0.312f, 0.12f, 0.001f);
  std::cout << "Quat: " << std::endl;
  std::cout << q << std::endl;
  
  return 0;
}