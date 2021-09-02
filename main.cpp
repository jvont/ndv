#include <ndv/vec.h>

#include <iostream>

// TODO: look into workarounds for custom member amounts per class
// https://stackoverflow.com/questions/3836648/structure-or-class-with-variable-number-of-members

int main()
{
  Vec3<int> v(1, 5, 4);
  v.x() += 1;
  v[0] += 1;

  v.y() = 2;

  v.z() *= 2;

  std::cout << v.to_string() << std::endl;

  return 0;
}