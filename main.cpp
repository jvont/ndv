#include <ndv/vec/vec2.h>

#include <iostream>
#include <array>

int main()
{
  // Vec2<int> vi(1, 2);
  // vi += vi;

  Vec2<float> vf(1.0f, 2.9f);
  vf += vf;

  std::cout << vf.norm() << std::endl;

  return 0;
}